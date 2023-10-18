// Bill_DLG.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_Client_2.h"
#include "afxdialogex.h"
#include "Bill_DLG.h"
#include "MFC_Client_2Dlg.h"
#include "CLIENT_CAFE_DLG.h"
#include <afxdb.h>
#include "Document.h"
#include "Info.h"

// Bill_DLG 대화 상자

IMPLEMENT_DYNAMIC(Bill_DLG, CDialogEx)

Bill_DLG::Bill_DLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BILL, pParent)
{

}

Bill_DLG::~Bill_DLG()
{
}

void Bill_DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, bill_list);
}


BEGIN_MESSAGE_MAP(Bill_DLG, CDialogEx)
END_MESSAGE_MAP()


// Bill_DLG 메시지 처리기


BOOL Bill_DLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	LPWSTR texts[6] = { TEXT("음료명"),TEXT("ICE/HOT"), TEXT("단가"), TEXT("수량"), TEXT("금액") };
	int widths[6] = { 100,100,60, 70,100 };
	LV_COLUMN col;			//list view 컬럼을 사용하기 위해
	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_CENTER;			//정렬은 센터로

	for (int i = 0; i < 6; i++)
	{
		col.pszText = texts[i];
		col.iSubItem = i;
		col.cx = widths[i];
		bill_list.InsertColumn(i, &col);
	}

	Document* doc = Document::GetSingleton();
	for (int i = 0; i < doc->GetLastSN_P1() - 1; i++)
	{
		bill_list.InsertItem(i, doc->infoes[i]->Get_pro_name());
		bill_list.SetItemText(i, 1, doc->infoes[i]->Get_ice_hot());

		int str = doc->infoes[i]->Get_money();
		CString strstr;
		strstr.Format(_T("%d"), str);

		int str1 = doc->infoes[i]->Get_num();
		CString strstr1;
		strstr1.Format(_T("%d"), str1);

		int str2 = doc->infoes[i]->Get_hap();
		CString strstr2;
		strstr2.Format(_T("%d"), str2);


		bill_list.SetItemText(i, 2, strstr1);
		bill_list.SetItemText(i, 3, strstr);
		bill_list.SetItemText(i, 4, strstr2);

		SetDlgItemText(IDC_EDIT1, doc->infoes[i]->Get_date());
		SetDlgItemInt(IDC_EDIT9, doc->infoes[i]->Get_point());

	}
	CMFCClient2Dlg* pParent = (CMFCClient2Dlg*)GetParent();
	CString id;
	id = pParent->LOGIN_ID;
	SetDlgItemText(IDC_EDIT8, id);


	int nItemCount = bill_list.GetItemCount();
	int total_money = 0;
	for (int i = 0; i < nItemCount; i++) {
		// 4번째 열의 값을 가져와서 int로 변환하여 더함
		int value_in_column_4 = _ttoi(bill_list.GetItemText(i, 4));

		total_money += value_in_column_4;

	}

	SetDlgItemInt(IDC_EDIT4, total_money);




	return TRUE;  // return TRUE unless you set the focus to a control
}
