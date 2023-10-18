#pragma once
#include "afxdialogex.h"


// CusManageDlg 대화 상자

class CusManageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CusManageDlg)

public:
	CusManageDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CusManageDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CUSMANAGE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
