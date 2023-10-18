#include "pch.h"
// ClientSocket.cpp : ���� �����Դϴ�.
//


#include "CLIENT_CAFE_DLG.h"
#include "CClientSocket.h"


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
    TCHAR szBuffer[1024];
    ZeroMemory(szBuffer, sizeof(szBuffer));

    if (Receive(szBuffer, sizeof(szBuffer)) > 0) {
        SendMessage(m_hWnd, WM_CLIENT_RECV, 0, (LPARAM)szBuffer);
    }

    CSocket::OnReceive(nErrorCode);
}

void CClientSocket::OnClose(int nErrorCode)
{
    // TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
    ShutDown();
    Close();

    CSocket::OnClose(nErrorCode);

    AfxMessageBox(_T("ERROR:Disconnected from server!"));
    PostQuitMessage(0);
}