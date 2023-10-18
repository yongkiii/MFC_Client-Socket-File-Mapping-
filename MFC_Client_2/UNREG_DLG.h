#pragma once
#include "afxdialogex.h"


// UNREG_DLG 대화 상자

class UNREG_DLG : public CDialogEx
{
	DECLARE_DYNAMIC(UNREG_DLG)

public:
	UNREG_DLG(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~UNREG_DLG();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNREG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString UNREG_ID;
	CString UNREG_PW;
	CString UNREG_PW_OK;
	afx_msg void OnBnClickedButtonUnreg();
};
