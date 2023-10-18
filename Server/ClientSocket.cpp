#include "pch.h"
#include "ClientSocket.h"
// ClientSocket.cpp : ���� �����Դϴ�.
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


// CClientSocket ��� �Լ�
void CClientSocket::SetWnd(HWND hWnd)
{
	m_hWnd = hWnd;
}

void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CString strTmp = _T(""), strIPAddress = _T("");
	UINT uPortNumber = 0;
	TCHAR strBuffer[1024];
	ZeroMemory(strBuffer, sizeof(strBuffer));

	GetPeerName(strIPAddress, uPortNumber);
	if (Receive(strBuffer, sizeof(strBuffer)) > 0) { // ���޵� ������(���ڿ�)�� ���� ���
		//strTmp.Format(_T("[%s : %d]: %s"), strIPAddress, uPortNumber, strBuffer);
		strTmp.Format(_T("%s"),strBuffer);

	}
	//Main Window�� Send
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
//    if (Receive(strBuffer, sizeof(strBuffer)) > 0) { // ���޵� ������(���ڿ�)�� ���� ���
//        // �����͸� Ȯ��
//        if (lstrlen(strBuffer) >= 9 && _tcsncmp(strBuffer, _T("[���Ÿ��]"), 9) == 0) 
//        {
//            m_list_buy.InsertString(-1, strBuffer);
//            m_list_buy.InsertString(1, _T("sdf"));
//            //m_list_buy.SetCurSel(strBuffer.GetCount() - 1);
//            // �����Ͱ� [���Ÿ��]���� �����ϴ� ��� ó��
//            // ���⿡�� �����͸� ó���ϰų� ���� â���� ����
//
//        }
//        else {
//            // �����Ͱ� [���Ÿ��]���� �������� �ʴ� ��� ó��
//        }
//
//        strTmp.Format(_T("[%s : %d]: %s"), strIPAddress, uPortNumber, strBuffer);
//    }
//    // Main Window�� Send
//    SendMessage(m_hWnd, WM_CLIENT_MSG_RECV, 0, (LPARAM)((LPCTSTR)strTmp));
//
//    CSocket::OnReceive(nErrorCode);
//}


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	SendMessage(m_hWnd, WM_CLIENT_CLOSE, 0, (LPARAM)this);
	CSocket::OnClose(nErrorCode);
}
