#pragma once
#include "afxdialogex.h"

#include "ClientSocket.h"
#include "ServerSocket.h"
// Message_DLG 대화 상자

class Message_DLG : public CDialogEx
{
	DECLARE_DYNAMIC(Message_DLG)

public:
	Message_DLG(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Message_DLG();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Message };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	CClientSocket* m_pClientSocket;
	CServerSocket* m_pServerSocket;
public:
	CPtrList m_ptrClientSocketList; //For manage Client Sockets
protected:
	afx_msg LRESULT OnAcceptSocket(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientMsgRecv(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnClientClose(WPARAM wParam, LPARAM lParam);
public:
	CListBox m_list_msg;
	CListBox m_list_client;
};
