// SaleHistoryDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Server.h"
#include "afxdialogex.h"
#include "SaleHistoryDlg.h"

#include "Server.h"
#include "..\\SalesDB\SalesManager.h"
#pragma comment(lib,"../x64/Debug/SalesDB.lib")

// SaleHistoryDlg 대화 상자

IMPLEMENT_DYNAMIC(SaleHistoryDlg, CDialogEx)

SaleHistoryDlg::SaleHistoryDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SALESHISTORY_DIALOG, pParent)
	, mcdate(COleDateTime::GetCurrentTime())
{

}

SaleHistoryDlg::~SaleHistoryDlg()
{
}

void SaleHistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, mc);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR1, mcdate);
}


BEGIN_MESSAGE_MAP(SaleHistoryDlg, CDialogEx)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, &SaleHistoryDlg::OnMcnSelchangeMonthcalendar1)
END_MESSAGE_MAP()


// SaleHistoryDlg 메시지 처리기


void SaleHistoryDlg::OnMcnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	UpdateData();
	SalesMap salmap;
	manager.SetConnStr(TEXT("DSN=MFC;uid=scott;PWD=tiger"));
	manager.SelectAll(salmap);

	CString mcdatestr = mcdate.Format(_T("%Y-%m-%d"));

	Sales* sales = new Sales(CString("sid자리"), 500, CString("주문음료이름"), CString("핫인지아이스인지"), 5000, 5, 25000, CString("주문날짜"));

	int moneysum = 0;

	for (SIter seek = salmap.begin(); seek != salmap.end(); seek++)
	{
		sales = (*seek).second;

		CString currid = sales->GetSID();
		CString currdate = sales->GetSDate();
		if (currdate == mcdatestr)
		{
			moneysum = moneysum + (sales->GetSHapMoney());
		}
	}

	SetDlgItemInt(IDC_EDIT_SALEHISTORY, moneysum);
}
