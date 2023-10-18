// Message_DLG.cpp: 구현 파일
//

#include "pch.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"
#include "Message_DLG.h"
#include "ServerSocket.h"
#include "ClientSocket.h"

// Message_DLG 대화 상자

IMPLEMENT_DYNAMIC(Message_DLG, CDialogEx)

Message_DLG::Message_DLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Message, pParent)
{

}

Message_DLG::~Message_DLG()
{
}

void Message_DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MSG, m_list_msg);
	DDX_Control(pDX, IDC_LIST_CLIENT, m_list_client);
}


BEGIN_MESSAGE_MAP(Message_DLG, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_ACCEPT_SOCKET, &Message_DLG::OnAcceptSocket)
	ON_MESSAGE(WM_CLIENT_MSG_RECV, &Message_DLG::OnClientMsgRecv)
	ON_MESSAGE(WM_CLIENT_CLOSE, &Message_DLG::OnClientClose)
END_MESSAGE_MAP()



BOOL Message_DLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}


	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//Listen 소켓 초기화
	m_pServerSocket = new CServerSocket;
	m_pServerSocket->SetWnd(this->m_hWnd);

	//소켓 Listen하기
	m_pServerSocket->Create(10200);
	m_pServerSocket->Listen();

	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}
// Message_DLG 메시지 처리기
afx_msg LRESULT Message_DLG::OnAcceptSocket(WPARAM wParam, LPARAM lParam)
{
	CString str;
	m_pClientSocket = (CClientSocket*)lParam;
	m_ptrClientSocketList.AddTail(m_pClientSocket);

	str.Format(_T("Client (%d)"), (int)(m_pClientSocket));
	m_list_client.InsertString(-1, str);

	m_pClientSocket = NULL;
	delete m_pClientSocket;

	return 0;
}


afx_msg LRESULT Message_DLG::OnClientMsgRecv(WPARAM wParam, LPARAM lParam)
{
	LPCTSTR lpszStr = (LPCTSTR)lParam;

	//BroadCasting
	POSITION pos = m_ptrClientSocketList.GetHeadPosition();

	while (pos != NULL)
	{
		CClientSocket* pClient = (CClientSocket*)m_ptrClientSocketList.GetNext(pos);
		if (pClient != NULL)
		{
			//UNICODE 사용하면 기존 메모리크기 *2 해야함
			//Client에 Broadcasting하기
			pClient->Send(lpszStr, lstrlen(lpszStr) * 2);
		}
	}

	//m_list_msg에 메시지 추가
	m_list_msg.InsertString(-1, lpszStr);
	m_list_msg.SetCurSel(m_list_msg.GetCount() - 1);

	return 0;
}


afx_msg LRESULT Message_DLG::OnClientClose(WPARAM wParam, LPARAM lParam)
{
	CClientSocket* pClient = (CClientSocket*)lParam;
	CString str;
	UINT idx = 0;
	POSITION pos = m_ptrClientSocketList.Find(pClient);

	if (pos != NULL)
	{
		//m_list_client에서 해당 Client 삭제
		str.Format(_T("Client (%d)"), (int)pClient);
		idx = m_list_client.SelectString(-1, (LPCTSTR)str);
		m_list_client.DeleteString(idx);

		//CPtrList에서도 해당 Client 삭제
		m_ptrClientSocketList.RemoveAt(pos);
	}

	return 0;
}