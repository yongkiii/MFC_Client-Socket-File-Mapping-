﻿
// MFC_ClientDlg.h: 헤더 파일
//

#pragma once


// CMFCClient2Dlg 대화 상자
class CMFCClient2Dlg : public CDialogEx
{
	// 생성입니다.
public:
	CMFCClient2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


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
	afx_msg void OnBnClickedButtonReg();
	afx_msg void OnBnClickedButtonUnreg();
	afx_msg void OnBnClickedButtonLogin();
	CString LOGIN_ID;
	CString LOGIN_PW;
};
