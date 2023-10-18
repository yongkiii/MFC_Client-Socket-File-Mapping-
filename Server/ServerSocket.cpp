#include "pch.h"
#include "ServerSocket.h"
// ServerSocket.cpp : ���� �����Դϴ�.

#include "ServerSocket.h"


// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket ��� �Լ�
void CServerSocket::SetWnd(HWND hWnd)
{
    m_hWnd = hWnd;
}

void CServerSocket::OnAccept(int nErrorCode)
{
    // TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
    CClientSocket* pClient = new CClientSocket; //Client ���� ������ �߰�

    if (Accept(*pClient))  //Listen���� Ŭ���̾�Ʈ ������ Ȯ���ϸ�
    {
        pClient->SetWnd(m_hWnd); //Client���Ͽ� �����ڵ� ����
    }
    else    //Ŭ���̾�Ʈ ���� ������
    {
        delete pClient;
        AfxMessageBox(_T("ERROR : Failed can't accept new Client!"));
    }

    SendMessage(m_hWnd, WM_ACCEPT_SOCKET, 0, (LPARAM)pClient);
    CSocket::OnAccept(nErrorCode);
}
