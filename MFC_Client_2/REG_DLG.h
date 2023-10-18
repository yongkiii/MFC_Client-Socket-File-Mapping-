#pragma once
#include "afxdialogex.h"


// REG_DLG 대화 상자

class REG_DLG : public CDialogEx
{
	DECLARE_DYNAMIC(REG_DLG)

public:
	REG_DLG(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~REG_DLG();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString REG_ID;
	CString REG_PW;
	CString REG_PW_OK;
	CString REG_NAME;
	CDateTimeCtrl REG_DATE_CON;
	COleDateTime REG_DATE;
	CString REG_ADDR;
	CString REG_PHONE;
	afx_msg void OnBnClickedButtonReg();
	afx_msg void OnBnClickedButtonCancel();
};
