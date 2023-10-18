#pragma once
#include "afxdialogex.h"
#include "../SalesDB/SalesManager.h"


// SaleHistoryDlg 대화 상자

class SaleHistoryDlg : public CDialogEx
{
	SalesManager manager;
	DECLARE_DYNAMIC(SaleHistoryDlg)

public:
	SaleHistoryDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~SaleHistoryDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SALESHISTORY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// monthcalendar
	CMonthCalCtrl mc;
	afx_msg void OnMcnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult);
	// monthcalendardate
	COleDateTime mcdate;
};
