
// ServerDlg.h: 헤더 파일
//
#pragma once
#include "../SalesDB/SalesManager.h"
#include "ClientSocket.h"
#include "ServerSocket.h"
#pragma once

// CServerDlg 대화 상자
class CServerDlg : public CDialogEx
{
	SalesManager manager;
// 생성입니다.
public:
	CServerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVER };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

private:
// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSalesmanage();
	afx_msg void OnBnClickedButtonCustomermanage();
	CListCtrl list_order;
	CListCtrl list_ordermenu;
	afx_msg void OnBnClickedButtonOrderchange();
	afx_msg void OnBnClickedButtonCustomerquestion();
	afx_msg void OnBnClickedButtonOrdercancel();
	afx_msg void OnLvnItemchangedListOrder(NMHDR* pNMHDR, LRESULT* pResult);

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
	CListBox m_list_buy;
	CListBox m_list_all;
	afx_msg void OnBnClickedButtonOrdercreate();
	CString orderlistsum;
	afx_msg void OnBnClickedButtonOrderconfirm();
	// 콤보박스 컨트롤
	CComboBox combo_count_control;
	// 콤보박스 카운트 변수
	CString combo_count_str;
	afx_msg void OnBnClickedButtonChangecount();
	afx_msg void OnLvnItemchangedListOrdermenu(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCbnSelchangeComboChangecount();
};
