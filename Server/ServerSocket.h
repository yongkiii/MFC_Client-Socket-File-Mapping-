#pragma once

#include "ClientSocket.h"
// CServerSocket ��� ����Դϴ�.
#define WM_ACCEPT_SOCKET WM_USER+1

class CServerSocket : public CSocket
{
public:
	CServerSocket();
	virtual ~CServerSocket();
	void SetWnd(HWND hWnd);
	HWND m_hWnd;
	virtual void OnAccept(int nErrorCode);
};

