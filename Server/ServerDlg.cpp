
// ServerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"
#include "ServerSocket.h"
#include "ClientSocket.h"
#include "SaleHistoryDlg.h"
#include "CusManageDlg.h"
#include <afxdb.h>
#include "Message_DLG.h"
#include "SelectedOrder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
#include "..\\SalesDB\SalesManager.h"
#pragma comment(lib,"../x64/Debug/SalesDB.lib")

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CServerDlg 대화 상자



CServerDlg::CServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVER_DIALOG, pParent)
	, orderlistsum(_T(""))
	, combo_count_str(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MSG, m_list_msg);
	DDX_Control(pDX, IDC_LIST_CLIENT, m_list_client);
	DDX_Control(pDX, IDC_LIST_ORDER, list_order);
	DDX_Control(pDX, IDC_LIST_ORDERMENU, list_ordermenu);
	DDX_Control(pDX, IDC_LIST_BUY, m_list_buy);
	DDX_Control(pDX, IDC_LIST_ALL, m_list_all);
	DDX_Text(pDX, IDC_STATIC_ORDERSUM, orderlistsum);
	DDX_Control(pDX, IDC_COMBO_CHANGECOUNT, combo_count_control);
	DDX_CBString(pDX, IDC_COMBO_CHANGECOUNT, combo_count_str);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_ACCEPT_SOCKET, &CServerDlg::OnAcceptSocket)
	ON_MESSAGE(WM_CLIENT_MSG_RECV, &CServerDlg::OnClientMsgRecv)
	ON_MESSAGE(WM_CLIENT_CLOSE, &CServerDlg::OnClientClose)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ORDER, &CServerDlg::OnLvnItemchangedListOrder)
	ON_BN_CLICKED(IDC_BUTTON_SALESMANAGE, &CServerDlg::OnBnClickedButtonSalesmanage)
	//ON_BN_CLICKED(IDC_BUTTON_CUSTOMERMANAGE, &CServerDlg::OnBnClickedButtonCustomermanage)
	ON_BN_CLICKED(IDC_BUTTON_ORDERCHANGE, &CServerDlg::OnBnClickedButtonOrderchange)
	ON_BN_CLICKED(IDC_BUTTON_CUSTOMERQUESTION, &CServerDlg::OnBnClickedButtonCustomerquestion)
	ON_BN_CLICKED(IDC_BUTTON_ORDERCANCEL, &CServerDlg::OnBnClickedButtonOrdercancel)
	ON_BN_CLICKED(IDC_BUTTON_ORDERCREATE, &CServerDlg::OnBnClickedButtonOrdercreate)
	ON_BN_CLICKED(IDC_BUTTON_ORDERCONFIRM, &CServerDlg::OnBnClickedButtonOrderconfirm)
	ON_BN_CLICKED(IDC_BUTTON_CHANGECOUNT, &CServerDlg::OnBnClickedButtonChangecount)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_ORDERMENU, &CServerDlg::OnLvnItemchangedListOrdermenu)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANGECOUNT, &CServerDlg::OnCbnSelchangeComboChangecount)
END_MESSAGE_MAP()


// CServerDlg 메시지 처리기

BOOL CServerDlg::OnInitDialog()
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	//TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	//콤보박스 초기화
	for (int i = 0; i < 50; i++)
	{
		CString str;
		str.Format(_T("%d"), i);
		combo_count_control.AddString(str);
	}

	
	//Listen 소켓 초기화
	m_pServerSocket = new CServerSocket;
	m_pServerSocket->SetWnd(this->m_hWnd);

	//소켓 Listen하기
	m_pServerSocket->Create(10200);
	m_pServerSocket->Listen();

	//
	list_order.InsertColumn(0, TEXT("No"), 0, 60);
	list_order.InsertColumn(1, TEXT("주문 날짜"), 0, 100);

	list_ordermenu.InsertColumn(0, TEXT("주문음료"), 0, 100);
	list_ordermenu.InsertColumn(1, TEXT("종류"), 0, 100);
	list_ordermenu.InsertColumn(2, TEXT("갯수"), 0, 40);
	list_ordermenu.InsertColumn(3, TEXT("금액"), 0, 100);
	list_ordermenu.InsertColumn(4, TEXT("합산"), 0, 100);


	SalesMap salmap;
	manager.SetConnStr(TEXT("DSN=MFC;uid=scott;PWD=tiger"));
	manager.SelectAll(salmap);

	Sales* sales = new Sales(CString("sid자리"), 500, CString("주문음료이름"), CString("핫인지아이스인지"), 5000, 5, 25000, CString("주문날짜"));

	int i = 0;
	//같은 주문이면 패스해서 리스트에 넣음
	CString previd;
	CString currid;
	CString prevdate;
	CString currdate;

	for (SIter seek = salmap.begin(); seek != salmap.end(); seek++)
	{
		sales = (*seek).second;

		currid = sales->GetSID();
		currdate = sales->GetSDate();
		if ((currid != previd) || (currdate != prevdate))
		{
			list_order.InsertItem(i, sales->GetSID());
			list_order.SetItemText(i, 1, sales->GetSDate());
			i++;
		}
		previd = currid;
		prevdate = currdate;
	}

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

afx_msg LRESULT CServerDlg::OnAcceptSocket(WPARAM wParam, LPARAM lParam)
{
	CString str;
	m_pClientSocket = (CClientSocket*)lParam;
	m_ptrClientSocketList.AddTail(m_pClientSocket);

	str.Format(_T("Client (%s)"),list_order.GetItemText(0,0));
	m_list_client.InsertString(-1, str);

	m_pClientSocket = NULL;
	delete m_pClientSocket;

	return 0;
}


afx_msg LRESULT CServerDlg::OnClientMsgRecv(WPARAM wParam, LPARAM lParam)
{
	LPCTSTR lpszStr = (LPCTSTR)lParam;
	CString receivedData(lpszStr); // 수신한 데이터를 CString으로 변환



	//------------------

	//CString receivedData(lpszStr); // 수신한 데이터를 CString으로 변환

	// 데이터가 [구매목록]으로 시작하는 경우
	if (receivedData.Find(_T("[구매목록]")) == 0)
	{
		// [구매목록]으로 시작하는 경우 m_list_buy에 추가
		m_list_buy.AddString(receivedData);
		m_list_buy.SetCurSel(m_list_buy.GetCount() - 1);
		 
	}
	else
	{
		// [구매목록]으로 시작하지 않는 경우 m_list_msg에 추가
		//m_list_msg.InsertString(-1, receivedData);
		m_list_msg.AddString(receivedData);
		m_list_msg.SetCurSel(m_list_msg.GetCount() - 1);
	}

	//------------------
	 
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


	////
	//int index = list_order.GetItemCount();
	//list_order.SetItemText(index, 1, lpszStr);

	return 0;
}


afx_msg LRESULT CServerDlg::OnClientClose(WPARAM wParam, LPARAM lParam)
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

void CServerDlg::OnBnClickedButtonSalesmanage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SaleHistoryDlg* reg = new SaleHistoryDlg();
	reg->Create(IDD_SALESHISTORY_DIALOG);
	reg->ShowWindow(SW_SHOW);
}


void CServerDlg::OnBnClickedButtonCustomermanage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CusManageDlg* reg = new CusManageDlg();
	reg->Create(IDD_CUSMANAGE_DIALOG);
	reg->ShowWindow(SW_SHOW);
}


void CServerDlg::OnBnClickedButtonOrderchange()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}


void CServerDlg::OnBnClickedButtonCustomerquestion()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	Message_DLG* message = new Message_DLG();
	message->Create(IDD_Message);
	message->ShowWindow(SW_SHOW);

}


void CServerDlg::OnBnClickedButtonOrdercancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos = list_order.GetFirstSelectedItemPosition();
	int index = list_order.GetNextSelectedItem(pos);
	if (index == -1)
	{
		return;
	}
	CString S_ID = list_order.GetItemText(index, 0);
	CString S_DATE = list_order.GetItemText(index, 1);
	manager.RemoveSales(S_ID, S_DATE);
	list_order.DeleteItem(index);
}


void CServerDlg::OnLvnItemchangedListOrder(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;


	POSITION pos = list_order.GetFirstSelectedItemPosition();
	int index = list_order.GetNextSelectedItem(pos);

	//클릭해서 얻어온 변수
	CString s_id;
	CString s_date;
	s_id = list_order.GetItemText(index, 0);
	s_date = list_order.GetItemText(index, 1);

	SelectedOrder* so = SelectedOrder::GetInstance();
	so->Set_SeletedID(s_id);
	so->Set_SeletedDATE(s_date);

	SalesMap salmap;
	manager.SetConnStr(TEXT("DSN=MFC;uid=scott;PWD=tiger"));
	manager.SelectAll(salmap);

	Sales* sales = new Sales(CString("sid자리"), 500, CString("주문음료이름"), CString("핫인지아이스인지"), 5000, 5, 25000, CString("주문날짜"));

	int i = 0;
	int moneysum = 0;

	for (SIter seek = salmap.begin(); seek != salmap.end(); seek++)
	{
		sales = (*seek).second;

		CString currid = sales->GetSID();
		CString currdate = sales->GetSDate();
		if ((currid == s_id) && (currdate == s_date))
		{
			list_ordermenu.InsertItem(i, sales->GetSProName());
			list_ordermenu.SetItemText(i, 1, sales->GetSIceHot());
			list_ordermenu.SetItemText(i, 2, sales->GetSNumStr());
			list_ordermenu.SetItemText(i, 3, sales->GetSMoneyStr());
			list_ordermenu.SetItemText(i, 4, sales->GetSHapMoneyStr());
			i++;
			moneysum = moneysum + (sales->GetSHapMoney());
		}
	}
	orderlistsum.Format(_T("%d"), moneysum);
	//list_order의 클릭이 변경되면 list_ordermenu 삭제
	if (index == -1)
	{
		while (list_ordermenu.GetItemCount() > 0)
		{
			list_ordermenu.DeleteAllItems();
		}
	}

	UpdateData(0);

}

//주문 확정
void CServerDlg::OnBnClickedButtonOrdercreate()
{

	while (list_order.GetItemCount() > 0)
	{
		list_order.DeleteAllItems();
	}

	SalesMap salmap;
	manager.SetConnStr(TEXT("DSN=MFC;uid=scott;PWD=tiger"));
	manager.SelectAll(salmap);

	Sales* sales = new Sales(CString("sid자리"), 500, CString("주문음료이름"), CString("핫인지아이스인지"), 5000, 5, 25000, CString("주문날짜"));

	int i = 0;
	//같은 주문이면 패스해서 리스트에 넣음
	CString previd;
	CString currid;
	CString prevdate;
	CString currdate;

	for (SIter seek = salmap.begin(); seek != salmap.end(); seek++)
	{
		sales = (*seek).second;

		currid = sales->GetSID();
		currdate = sales->GetSDate();
		if ((currid != previd) || (currdate != prevdate))
		{
			list_order.InsertItem(i, sales->GetSID());
			list_order.SetItemText(i, 1, sales->GetSDate());
			i++;
		}
		previd = currid;
		prevdate = currdate;
	}
}


void CServerDlg::OnBnClickedButtonOrderconfirm()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CServerDlg::OnBnClickedButtonChangecount()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	SelectedOrder* so = SelectedOrder::GetInstance();

	int snum = _ttoi(combo_count_str);

	manager.SetConnStr(TEXT("DSN=MFC;uid=scott;PWD=tiger"));
	manager.UpdateItemCount(so->Get_SeletedID(), so->Get_SeletedDATE(), so->Get_SeletedProNAME(), snum);

}


void CServerDlg::OnLvnItemchangedListOrdermenu(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	POSITION pos = list_ordermenu.GetFirstSelectedItemPosition();
	int index = list_ordermenu.GetNextSelectedItem(pos);

	if (index == -1)
	{
		GetDlgItem(IDC_COMBO_CHANGECOUNT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_CHANGECOUNT)->ShowWindow(SW_HIDE);
	}
	GetDlgItem(IDC_COMBO_CHANGECOUNT)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_CHANGECOUNT)->ShowWindow(SW_SHOW);

	SelectedOrder* so = SelectedOrder::GetInstance();
	so->Set_SeletedProNAME(list_ordermenu.GetItemText(index, 0));

}


void CServerDlg::OnCbnSelchangeComboChangecount()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
