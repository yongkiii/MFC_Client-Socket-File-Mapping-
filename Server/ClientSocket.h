#pragma once
#define WM_CLIENT_RECV WM_USER+1

#define WM_CLIENT_MSG_RECV WM_USER+2
#define WM_CLIENT_CLOSE WM_USER+3
// CClientSocket ��� ����Դϴ�.

class CClientSocket : public CSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	void SetWnd(HWND hWnd);
	HWND m_hWnd;
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};