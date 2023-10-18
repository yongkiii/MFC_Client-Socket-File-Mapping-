#include "pch.h"
#include "ClientSocket.h"
// ClientSocket.cpp : 구현 파일입니다.
//
#include "ServerDlg.h"

#include "ClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 멤버 함수
void CClientSocket::SetWnd(HWND hWnd)
{
	m_hWnd = hWnd;
}

void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CString strTmp = _T(""), strIPAddress = _T("");
	UINT uPortNumber = 0;
	TCHAR strBuffer[1024];
	ZeroMemory(strBuffer, sizeof(strBuffer));

	GetPeerName(strIPAddress, uPortNumber);
	if (Receive(strBuffer, sizeof(strBuffer)) > 0) { // 전달된 데이터(문자열)가 있을 경우
		//strTmp.Format(_T("[%s : %d]: %s"), strIPAddress, uPortNumber, strBuffer);
		strTmp.Format(_T("%s"),strBuffer);

	}
	//Main Window에 Send
	SendMessage(m_hWnd, WM_CLIENT_MSG_RECV, 0, (LPARAM)((LPCTSTR)strTmp));

	CSocket::OnReceive(nErrorCode);
}

//void CClientSocket::OnReceive(int nErrorCode)
//{
//    CString strTmp = _T(""), strIPAddress = _T("");
//    UINT uPortNumber = 0;
//    TCHAR strBuffer[1024];
//    ZeroMemory(strBuffer, sizeof(strBuffer));
//
//    GetPeerName(strIPAddress, uPortNumber);
//    if (Receive(strBuffer, sizeof(strBuffer)) > 0) { // 전달된 데이터(문자열)가 있을 경우
//        // 데이터를 확인
//        if (lstrlen(strBuffer) >= 9 && _tcsncmp(strBuffer, _T("[구매목록]"), 9) == 0) 
//        {
//            m_list_buy.InsertString(-1, strBuffer);
//            m_list_buy.InsertString(1, _T("sdf"));
//            //m_list_buy.SetCurSel(strBuffer.GetCount() - 1);
//            // 데이터가 [구매목록]으로 시작하는 경우 처리
//            // 여기에서 데이터를 처리하거나 메인 창으로 전달
//
//        }
//        else {
//            // 데이터가 [구매목록]으로 시작하지 않는 경우 처리
//        }
//
//        strTmp.Format(_T("[%s : %d]: %s"), strIPAddress, uPortNumber, strBuffer);
//    }
//    // Main Window에 Send
//    SendMessage(m_hWnd, WM_CLIENT_MSG_RECV, 0, (LPARAM)((LPCTSTR)strTmp));
//
//    CSocket::OnReceive(nErrorCode);
//}


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	SendMessage(m_hWnd, WM_CLIENT_CLOSE, 0, (LPARAM)this);
	CSocket::OnClose(nErrorCode);
}
