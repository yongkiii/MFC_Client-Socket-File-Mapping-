#pragma once
#include "afxdialogex.h"


// Bill_DLG 대화 상자

class Bill_DLG : public CDialogEx
{
	DECLARE_DYNAMIC(Bill_DLG)

public:
	Bill_DLG(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~Bill_DLG();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BILL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString point;
	CString pro_name;
	CString ice_hot;
	CString money;
	CString num;
	CString hap;
	CString date;

	virtual BOOL OnInitDialog();
	CListCtrl bill_list;
};
