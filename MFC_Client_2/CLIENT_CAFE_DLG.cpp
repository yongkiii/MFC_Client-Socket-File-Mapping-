// CLIENT_CAFE_DLG.cpp: 구현 파일

#pragma comment(lib,"ws2_32")
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>

#include "pch.h"
#include "MFC_Client_2.h"
#include "afxdialogex.h"
#include "CLIENT_CAFE_DLG.h"
#include "MFC_Client_2Dlg.h"
#include <afxdb.h>
#include "Bill_DLG.h"
#include "My_Info.h"

#include "CClientSocket.h"

#include "../SelLib/SelReq.h"
#include "../LogLib/LogoutReq.h"

#include<string.h>
#include <stdlib.h>
#pragma comment(lib,"..\\x64\\Debug\\SelLib")

#include "Info.h"
#include "Document.h"

#include <vector>
#pragma warning(disable:4996)
using namespace std;
// CLIENT_CAFE_DLG 대화 상자

IMPLEMENT_DYNAMIC(CLIENT_CAFE_DLG, CDialogEx)

CLIENT_CAFE_DLG::CLIENT_CAFE_DLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLIENT_CAFE, pParent)
	, edit_spin(_T(""))

	, message(_T(""))
{

}

CLIENT_CAFE_DLG::~CLIENT_CAFE_DLG()
{
}

void CLIENT_CAFE_DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_RADIO1, drink_ice_1);
	DDX_Control(pDX, IDC_RADIO2, drink_hot_1);

	DDX_Control(pDX, IDC_BUTTON_CAFE1, drink_1);
	DDX_Control(pDX, IDC_BUTTON_CAFE2, drink_2);
	DDX_Control(pDX, IDC_BUTTON_CAFE3, drink_3);
	DDX_Control(pDX, IDC_BUTTON_CAFE4, drink_4);
	DDX_Control(pDX, IDC_BUTTON_CAFE5, drink_5);
	DDX_Control(pDX, IDC_BUTTON_CAFE6, drink_6);
	DDX_Control(pDX, IDC_LIST1, temp_list);
	DDX_Control(pDX, IDC_LIST2, point_list);
	DDX_Text(pDX, IDC_EDIT_SPIN2, edit_spin);
	DDX_Text(pDX, IDC_MESSAGE, message);
	DDX_Control(pDX, IDC_MESSAGE, m_edit_send);
	DDX_Control(pDX, IDC_LIST3, m_list_msg);
}


BEGIN_MESSAGE_MAP(CLIENT_CAFE_DLG, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CLIENT_CAFE_DLG::OnBnClickedButtonLogout)
	ON_BN_CLICKED(IDC_BUTTON_CAFE1, &CLIENT_CAFE_DLG::OnBnClickedButtonCafe1)
	ON_BN_CLICKED(IDC_BUTTON_CAFE2, &CLIENT_CAFE_DLG::OnBnClickedButtonCafe2)
	ON_BN_CLICKED(IDC_BUTTON_CAFE3, &CLIENT_CAFE_DLG::OnBnClickedButtonCafe3)
	ON_BN_CLICKED(IDC_BUTTON_CAFE4, &CLIENT_CAFE_DLG::OnBnClickedButtonCafe4)
	ON_BN_CLICKED(IDC_BUTTON_CAFE5, &CLIENT_CAFE_DLG::OnBnClickedButtonCafe5)
	ON_BN_CLICKED(IDC_BUTTON_CAFE6, &CLIENT_CAFE_DLG::OnBnClickedButtonCafe6)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_QUANTITY2, &CLIENT_CAFE_DLG::OnDeltaposSpinQuantity2)
	ON_BN_CLICKED(IDC_BUTTON_POINT, &CLIENT_CAFE_DLG::OnBnClickedButtonPoint)
	ON_BN_CLICKED(IDC_BUTTON1_BUY, &CLIENT_CAFE_DLG::OnBnClickedButton1Buy)
	ON_BN_CLICKED(IDC_BUTTON_MENU_DEL, &CLIENT_CAFE_DLG::OnBnClickedButtonMenuDel)
	ON_BN_CLICKED(IDC_BUTTON_MENU_MOD, &CLIENT_CAFE_DLG::OnBnClickedButtonMenuMod)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CLIENT_CAFE_DLG::OnBnClickedButtonSend)
	ON_MESSAGE(WM_CLIENT_RECV, &CLIENT_CAFE_DLG::OnClientRecv)
END_MESSAGE_MAP()


// CLIENT_CAFE_DLG 메시지 처리기


void CLIENT_CAFE_DLG::OnBnClickedButtonLogout()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	My_Info* mi = My_Info::GetInstance();

	char id[MAX_ID_LEN] = "";
	char pw[MAX_PW_LEN] = "";

	HANDLE hPipe = CreateFile(REG_PNAME, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE,
		0, OPEN_EXISTING, 0, 0);

	CString cstrID = mi->Get_id();
	CString cstrPW = mi->Get_pw();

	CStringA cstrAID(cstrID);
	CStringA cstrAPW(cstrPW);

	const char* myid = cstrAID;
	const char* mypw = cstrAPW;

	LogoutReq* lor = new LogoutReq(myid, mypw);
	lor->Send(hPipe);
	delete lor;
	CloseHandle(hPipe);
	printf("로그 아웃 하였습니다.\n");
	EndDialog(0);
}

SOCKET CLIENT_CAFE_DLG::Connect()
{
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//2.연결
	SOCKADDR_IN servaddr = {};
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("192.168.0.58");
	servaddr.sin_port = htons(10202);
	if (connect(sock, (SOCKADDR*)&servaddr, sizeof(servaddr)) == -1)
	{
		closesocket(sock);
		return -1;
	}
	return sock;
}

BOOL CLIENT_CAFE_DLG::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=MFC; uid = scott;PWD=tiger"));

	m_ClientSocket.SetWnd(this->m_hWnd);
	m_ClientSocket.Create();
	if (m_ClientSocket.Connect(_T("192.168.0.58"), 10200) == FALSE) {
		AfxMessageBox(_T("ERROR : Failed to connect Server"));
		PostQuitMessage(0);
		return FALSE;
	}



	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	LPWSTR texts[6] = { TEXT("음료명"),TEXT("ICE/HOT"), TEXT("PRICE"), TEXT("BUY_NUM"), TEXT("TOTAL_MONEY") };
	int widths[6] = { 100,100,60, 70,100 };
	LV_COLUMN col;			//list view 컬럼을 사용하기 위해
	col.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col.fmt = LVCFMT_CENTER;			//정렬은 센터로

	for (int i = 0; i < 6; i++)
	{
		col.pszText = texts[i];
		col.iSubItem = i;
		col.cx = widths[i];
		temp_list.InsertColumn(i, &col);
	}
	// 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
   //====================================================================

	LPWSTR text1[3] = { TEXT("회원 아이디"),TEXT("회원명"), TEXT("포인트") };
	int width1[3] = { 100,100,60 };
	LV_COLUMN col1;			//list view 컬럼을 사용하기 위해
	col1.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	col1.fmt = LVCFMT_CENTER;			//정렬은 센터로

	for (int i = 0; i < 3; i++)
	{
		col1.pszText = text1[i];
		col1.iSubItem = i;
		col1.cx = width1[i];
		point_list.InsertColumn(i, &col1);
	}
	
	CMFCClient2Dlg* pParent = (CMFCClient2Dlg*)GetParent();

	CString id;
	id = pParent->LOGIN_ID;
	if (re == FALSE)
	{
		return TRUE;
	}
	CString pid;
	CRecordset rs(&db);

	wchar_t query_str[256] = TEXT("");
	wsprintf(query_str, TEXT("select* from UUSER where U_ID='%s'"), id);

	rs.Open(CRecordset::forwardOnly, query_str);
	int index = 0;
	while (!rs.IsEOF())
	{
		rs.GetFieldValue((short)0, u_id);
		rs.GetFieldValue((short)2, u_name);
		rs.GetFieldValue((short)6, point);


		point_list.InsertItem(index, u_id);
		point_list.SetItemText(index, 1, u_name);
		point_list.SetItemText(index, 2, point);



		rs.MoveNext();
		index++;
	}
	CString pointStr;
	int point = _wtoi(pointStr);
	final_point = point;

	rs.Close();
	db.Close();



	//====================================================================


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.


}


void CLIENT_CAFE_DLG::OnBnClickedButtonCafe1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//음료명
	int nItemNum = temp_list.GetItemCount();
	CString fd = TEXT("녹차라떼");
	temp_list.InsertItem(nItemNum, fd);

	//ICE/HOT
	int state_radio1 = drink_ice_1.GetCheck();
	int state_radio2 = drink_hot_1.GetCheck();
	CString ice_hot;
	if (state_radio1)
	{
		ice_hot = _T("ICE");
	}
	else if (state_radio2)
	{
		ice_hot = _T("HOT");
	}
	temp_list.SetItemText(nItemNum, 1, ice_hot);

	//가격
	int price = 2000;
	wchar_t price1[256];
	wsprintf(price1, TEXT("%d"), price);
	temp_list.SetItemText(nItemNum, 2, price1);

	//수량
	CString itemNumStr;
	itemNumStr.Format(_T("%d"), spin_value); // 정수를 문자열로 변환
	temp_list.SetItemText(nItemNum, 3, itemNumStr);

	//합 
	int result = spin_value * price;
	wchar_t result1[256];
	wsprintf(result1, TEXT("%d"), result);
	temp_list.SetItemText(nItemNum, 4, result1);

	//총 결제금액
	int total_money1 = GetDlgItemInt(IDC_TOTAL_MONEY);
	total_money = total_money1 + result;
	SetDlgItemInt(IDC_TOTAL_MONEY, total_money);

	//------
	//CDatabase db;
	//bool re = db.OpenEx(TEXT("DSN=MFC; uid = scott;PWD=tiger"));

	//if (re == FALSE)
	//{
	//	return;
	//}

	//CTime currentTime = CTime::GetCurrentTime();
	//CString currentDateStr = currentTime.Format(_T("%Y-%m-%d"));

	//CString query_str;
	//query_str.Format(_T("insert into DRINK (D_PRO_NAME, D_PRO_ICE_HOT, D_BUY_NUM, D_PRO_MONEY, D_DATE) values ('%s', '%s', %d, %d, '%s')"), fd, ice_hot, spin_value, price, currentDateStr);

	//db.ExecuteSQL(query_str);
	//db.Close();
}


void CLIENT_CAFE_DLG::OnBnClickedButtonCafe2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		//음료명
	int nItemNum = temp_list.GetItemCount();
	CString fd = TEXT("바닐라라떼");
	temp_list.InsertItem(nItemNum, fd);

	//ICE/HOT
	int state_radio1 = drink_ice_1.GetCheck();
	int state_radio2 = drink_hot_1.GetCheck();
	CString ice_hot;
	if (state_radio1)
	{
		ice_hot = _T("ICE");
	}
	else if (state_radio2)
	{
		ice_hot = _T("HOT");
	}
	temp_list.SetItemText(nItemNum, 1, ice_hot);

	//가격
	int price = 5500;
	wchar_t price1[256];
	wsprintf(price1, TEXT("%d"), price);
	temp_list.SetItemText(nItemNum, 2, price1);

	//수량
	CString itemNumStr;
	itemNumStr.Format(_T("%d"), spin_value); // 정수를 문자열로 변환
	temp_list.SetItemText(nItemNum, 3, itemNumStr);

	//합 
	int result = spin_value * price;
	wchar_t result1[256];
	wsprintf(result1, TEXT("%d"), result);
	temp_list.SetItemText(nItemNum, 4, result1);

	//총 결제금액
	int total_money1 = GetDlgItemInt(IDC_TOTAL_MONEY);
	total_money = total_money1 + result;
	SetDlgItemInt(IDC_TOTAL_MONEY, total_money);
	//------
	/*CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=MFC; uid = scott;PWD=tiger"));

	if (re == FALSE)
	{
		return;
	}

	CTime currentTime = CTime::GetCurrentTime();
	CString currentDateStr = currentTime.Format(_T("%Y-%m-%d"));

	CString query_str;
	query_str.Format(_T("insert into DRINK (D_PRO_NAME, D_PRO_ICE_HOT, D_BUY_NUM, D_PRO_MONEY, D_DATE) values ('%s', '%s', %d, %d, '%s')"), fd, ice_hot, spin_value, price, currentDateStr);

	db.ExecuteSQL(query_str);
	db.Close();*/
}


void CLIENT_CAFE_DLG::OnBnClickedButtonCafe3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		//음료명
	int nItemNum = temp_list.GetItemCount();
	CString fd = TEXT("아메리카노");
	temp_list.InsertItem(nItemNum, fd);

	//ICE/HOT
	int state_radio1 = drink_ice_1.GetCheck();
	int state_radio2 = drink_hot_1.GetCheck();
	CString ice_hot;
	if (state_radio1)
	{
		ice_hot = _T("ICE");
	}
	else if (state_radio2)
	{
		ice_hot = _T("HOT");
	}
	temp_list.SetItemText(nItemNum, 1, ice_hot);

	//가격
	int price = 1800;
	wchar_t price1[256];
	wsprintf(price1, TEXT("%d"), price);
	temp_list.SetItemText(nItemNum, 2, price1);

	//수량
	CString itemNumStr;
	itemNumStr.Format(_T("%d"), spin_value); // 정수를 문자열로 변환
	temp_list.SetItemText(nItemNum, 3, itemNumStr);

	//합 
	int result = spin_value * price;
	wchar_t result1[256];
	wsprintf(result1, TEXT("%d"), result);
	temp_list.SetItemText(nItemNum, 4, result1);

	//총 결제금액
	int total_money1 = GetDlgItemInt(IDC_TOTAL_MONEY);
	total_money = total_money1 + result;
	SetDlgItemInt(IDC_TOTAL_MONEY, total_money);

	//------
	/*CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=MFC; uid = scott;PWD=tiger"));

	if (re == FALSE)
	{
		return;
	}

	CTime currentTime = CTime::GetCurrentTime();
	CString currentDateStr = currentTime.Format(_T("%Y-%m-%d"));

	CString query_str;
	query_str.Format(_T("insert into DRINK (D_PRO_NAME, D_PRO_ICE_HOT, D_BUY_NUM, D_PRO_MONEY, D_DATE) values ('%s', '%s', %d, %d, '%s')"), fd, ice_hot, spin_value, price, currentDateStr);

	db.ExecuteSQL(query_str);
	db.Close();*/
}


void CLIENT_CAFE_DLG::OnBnClickedButtonCafe4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		//음료명
	int nItemNum = temp_list.GetItemCount();
	CString fd = TEXT("초코라떼");
	temp_list.InsertItem(nItemNum, fd);

	//ICE/HOT
	int state_radio1 = drink_ice_1.GetCheck();
	int state_radio2 = drink_hot_1.GetCheck();
	CString ice_hot;
	if (state_radio1)
	{
		ice_hot = _T("ICE");
	}
	else if (state_radio2)
	{
		ice_hot = _T("HOT");
	}
	temp_list.SetItemText(nItemNum, 1, ice_hot);

	//가격
	int price = 3500;
	wchar_t price1[256];
	wsprintf(price1, TEXT("%d"), price);
	temp_list.SetItemText(nItemNum, 2, price1);

	//수량
	CString itemNumStr;
	itemNumStr.Format(_T("%d"), spin_value); // 정수를 문자열로 변환
	temp_list.SetItemText(nItemNum, 3, itemNumStr);

	//합 
	int result = spin_value * price;
	wchar_t result1[256];
	wsprintf(result1, TEXT("%d"), result);
	temp_list.SetItemText(nItemNum, 4, result1);

	//총 결제금액
	int total_money1 = GetDlgItemInt(IDC_TOTAL_MONEY);
	total_money = total_money1 + result;
	SetDlgItemInt(IDC_TOTAL_MONEY, total_money);

	//------
	/*CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=MFC; uid = scott;PWD=tiger"));

	if (re == FALSE)
	{
		return;
	}

	CTime currentTime = CTime::GetCurrentTime();
	CString currentDateStr = currentTime.Format(_T("%Y-%m-%d"));

	CString query_str;
	query_str.Format(_T("insert into DRINK (D_PRO_NAME, D_PRO_ICE_HOT, D_BUY_NUM, D_PRO_MONEY, D_DATE) values ('%s', '%s', %d, %d, '%s')"), fd, ice_hot, spin_value, price, currentDateStr);

	db.ExecuteSQL(query_str);
	db.Close();*/
}


void CLIENT_CAFE_DLG::OnBnClickedButtonCafe5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		//음료명
	int nItemNum = temp_list.GetItemCount();
	CString fd = TEXT("헤이즐넛라떼");
	temp_list.InsertItem(nItemNum, fd);

	//ICE/HOT
	int state_radio1 = drink_ice_1.GetCheck();
	int state_radio2 = drink_hot_1.GetCheck();
	CString ice_hot;
	if (state_radio1)
	{
		ice_hot = _T("ICE");
	}
	else if (state_radio2)
	{
		ice_hot = _T("HOT");
	}
	temp_list.SetItemText(nItemNum, 1, ice_hot);

	//가격
	int price = 4200;
	wchar_t price1[256];
	wsprintf(price1, TEXT("%d"), price);
	temp_list.SetItemText(nItemNum, 2, price1);

	//수량
	CString itemNumStr;
	itemNumStr.Format(_T("%d"), spin_value); // 정수를 문자열로 변환
	temp_list.SetItemText(nItemNum, 3, itemNumStr);

	//합 
	int result = spin_value * price;
	wchar_t result1[256];
	wsprintf(result1, TEXT("%d"), result);
	temp_list.SetItemText(nItemNum, 4, result1);

	//총 결제금액
	int total_money1 = GetDlgItemInt(IDC_TOTAL_MONEY);
	total_money = total_money1 + result;
	SetDlgItemInt(IDC_TOTAL_MONEY, total_money);

	//------
	/*CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=MFC; uid = scott;PWD=tiger"));

	if (re == FALSE)
	{
		return;
	}

	CTime currentTime = CTime::GetCurrentTime();
	CString currentDateStr = currentTime.Format(_T("%Y-%m-%d"));

	CString query_str;
	query_str.Format(_T("insert into DRINK (D_PRO_NAME, D_PRO_ICE_HOT, D_BUY_NUM, D_PRO_MONEY, D_DATE) values ('%s', '%s', %d, %d, '%s')"), fd, ice_hot, spin_value, price, currentDateStr);

	db.ExecuteSQL(query_str);
	db.Close();*/
}


void CLIENT_CAFE_DLG::OnBnClickedButtonCafe6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		//음료명
	int nItemNum = temp_list.GetItemCount();
	CString fd = TEXT("아이스티");
	temp_list.InsertItem(nItemNum, fd);

	//ICE/HOT
	int state_radio1 = drink_ice_1.GetCheck();
	int state_radio2 = drink_hot_1.GetCheck();
	CString ice_hot;
	if (state_radio1)
	{
		ice_hot = _T("ICE");
	}
	else if (state_radio2)
	{
		ice_hot = _T("HOT");
	}
	temp_list.SetItemText(nItemNum, 1, ice_hot);

	//가격
	int price = 2300;
	wchar_t price1[256];
	wsprintf(price1, TEXT("%d"), price);
	temp_list.SetItemText(nItemNum, 2, price1);

	//수량
	CString itemNumStr;
	itemNumStr.Format(_T("%d"), spin_value); // 정수를 문자열로 변환
	temp_list.SetItemText(nItemNum, 3, itemNumStr);

	//합 
	int result = spin_value * price;
	wchar_t result1[256];
	wsprintf(result1, TEXT("%d"), result);
	temp_list.SetItemText(nItemNum, 4, result1);

	//총 결제금액
	int total_money1 = GetDlgItemInt(IDC_TOTAL_MONEY);
	total_money = total_money1 + result;
	SetDlgItemInt(IDC_TOTAL_MONEY, total_money);

	//------
	/*CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=MFC; uid = scott;PWD=tiger"));

	if (re == FALSE)
	{
		return;
	}

	CTime currentTime = CTime::GetCurrentTime();
	CString currentDateStr = currentTime.Format(_T("%Y-%m-%d"));

	CString query_str;
	query_str.Format(_T("insert into DRINK (D_PRO_NAME, D_PRO_ICE_HOT, D_BUY_NUM, D_PRO_MONEY, D_DATE) values ('%s', '%s', %d, %d, '%s')"), fd, ice_hot, spin_value, price, currentDateStr);

	db.ExecuteSQL(query_str);
	db.Close();*/
}

void CLIENT_CAFE_DLG::SetSpinValue(int spin_value)
{
	this->spin_value = spin_value;
}

void CLIENT_CAFE_DLG::OnDeltaposSpinQuantity2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (pNMUpDown->iDelta < 0)
	{
		spin_value++;
	}
	else
	{
		spin_value--;
	}
	SetDlgItemInt(IDC_EDIT_SPIN2, spin_value);
	*pResult = 0;
}


void CLIENT_CAFE_DLG::OnBnClickedButtonPoint()
{
	// 데이터베이스 열기
	CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=MFC; uid=scott; PWD=tiger"));

	CMFCClient2Dlg* pParent = (CMFCClient2Dlg*)GetParent();
	CString id = pParent->LOGIN_ID;

	CRecordset rs(&db);
	CString query_str;
	query_str.Format(_T("SELECT * FROM UUSER WHERE U_ID='%s'"), id);

	if (rs.Open(CRecordset::forwardOnly, query_str))
	{
		if (!rs.IsEOF())
		{
			CString point;
			rs.GetFieldValue((short)6, point);
			final_point = _ttoi(point);

		}
		//총 결제금액
		int point2 = _ttoi(point);
		final_point = _ttoi(point);

		int total_money1 = GetDlgItemInt(IDC_TOTAL_MONEY);
		if (total_money1 >= point2)
		{
			CString message;
			message.Format(_T("%s 포인트 사용"), point);
			AfxMessageBox(message);
			total_money = total_money1 - point2;
			SetDlgItemInt(IDC_TOTAL_MONEY, total_money);
			point2 = 0;
			point = "0";
			point_list.SetItemText(0, 2, point);
			final_point = 0;


			CString updateQuery;
			updateQuery.Format(_T("UPDATE UUSER SET U_POINT = 0 WHERE U_ID = '%s'"), id);
			db.ExecuteSQL(updateQuery);
		}
		else
		{
			MessageBox(TEXT("포인트가 부족합니다."));
		}
		rs.Close();
	}
	db.Close();
}


void CLIENT_CAFE_DLG::OnBnClickedButton1Buy()
{

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nItemCount = temp_list.GetItemCount();
	//열 개수 가져오기
	int nColumnCount = temp_list.GetHeaderCtrl()->GetItemCount();

	CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=MFC; uid=scott;PWD=tiger"));

	if (re == FALSE)
	{
		// Handle the case where database connection fails.
		return;
	}

	//SelReq* sr = new SelReq();
	CMFCClient2Dlg* pParent = (CMFCClient2Dlg*)GetParent();

	int pre_point = _ttoi(point_list.GetItemText(0, 2));
	CTime currentTime = CTime::GetCurrentTime();


	CString ID = pParent->LOGIN_ID;
	int D_POINT = 0;
	if (pre_point <= 0)
	{
		D_POINT = total_money * 0.05;
	}
	else
	{
		D_POINT = pre_point + total_money * 0.05;
	}
	CString D_PRO_NAME;
	CString D_PRO_ICE_HOT;
	int D_PRO_MONEY;
	int D_BUY_NUM;
	int D_HAP_MONEY;
	CString currentDateStr = currentTime.Format(_T("%Y-%m-%d"));
	char* id = new char[ID.GetLength()];

	char* DATE = new char[currentDateStr.GetLength()];


	for (int i = 0; i < nItemCount; i++)
	{


		int result = 0;
		SOCKET sock = Connect();
		if (Connect() == -1)
		{
			return;
		}
		strcpy_s(id, sizeof(id), CT2A(ID));

		D_PRO_NAME = temp_list.GetItemText(i, 0);
		char* NAME = new char[D_PRO_NAME.GetLength()];
		strcpy(NAME, (CT2A)D_PRO_NAME.GetBuffer(0));

		D_PRO_ICE_HOT = temp_list.GetItemText(i, 1);
		char* ICE_HOT = new char[D_PRO_ICE_HOT.GetLength()];
		strcpy_s(ICE_HOT, sizeof(ICE_HOT), CT2A(D_PRO_ICE_HOT));
		D_PRO_MONEY = _ttoi(temp_list.GetItemText(i, 2));
		D_BUY_NUM = _ttoi(temp_list.GetItemText(i, 3));
		D_HAP_MONEY = _ttoi(temp_list.GetItemText(i, 4));
		strcpy(DATE, (CT2A)currentDateStr.GetBuffer(0));




		SelReq* sr = new SelReq(id, D_POINT, NAME, ICE_HOT, D_PRO_MONEY, D_BUY_NUM, D_HAP_MONEY, DATE);

		sr->Send(sock);

		//Info===============
		Document* doc = Document::GetSingleton();
		doc->RegInfo(i, ID, D_POINT, D_PRO_NAME, D_PRO_ICE_HOT, D_PRO_MONEY, D_BUY_NUM, D_HAP_MONEY, currentDateStr);
		//===================
		// 
		//tcp--------------------------

		CString buydata;
		buydata.Format(_T("[구매목록] no : %d, user id : %s, point : %d, product name: %s, ice/hot: %s, money: %d, buy num: %d, hap money: %d, date: %s"),
			i, ID, D_POINT, D_PRO_NAME, D_PRO_ICE_HOT, D_PRO_MONEY, D_BUY_NUM, D_HAP_MONEY, currentDateStr);

		LPCTSTR lpctstr0 = buydata;
		m_ClientSocket.Send((LPVOID)(LPCTSTR)buydata, buydata.GetLength() * 2);
		//-----------------------------
		delete sr;
		closesocket(sock);

	}


	CString point_char;
	point_char.Format(_T("%d"), D_POINT);
	point_list.SetItemText(0, 2, point_char);

	//user db============
	CString updateQuery;
	updateQuery.Format(_T("UPDATE UUSER SET U_POINT = %d WHERE U_ID = '%s'"), D_POINT, ID);
	db.ExecuteSQL(updateQuery);
	db.Close();
	//===================

	total_money = 0;
	SetDlgItemInt(IDC_TOTAL_MONEY, total_money);

	temp_list.DeleteAllItems();
	Bill_DLG* bill = new Bill_DLG();
	bill->Create(IDD_BILL);
	bill->ShowWindow(SW_SHOW);
}



void CLIENT_CAFE_DLG::OnBnClickedButtonMenuDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos = temp_list.GetFirstSelectedItemPosition();
	int index = temp_list.GetNextSelectedItem(pos);

	////먼저 total_moeny 받아옴
	//int total_money1 = GetDlgItemInt(IDC_TOTAL_MONEY);

	////삭제 선택한 물품 돈
	//CString total = temp_list.GetItemText(index, 4);

	//int total_int = _ttoi(total);

	////받아온것-선택물품돈
	//total_money = total_money1 - total_int;

	//SetDlgItemInt(IDC_TOTAL_MONEY, total_money);



	if (index == -1)
	{
		return;
	}
	CString pno = temp_list.GetItemText(index, 0);
	int no = _wtoi(pno);
	temp_list.DeleteItem(index);


	int nItemCount = temp_list.GetItemCount();
	total_money = 0;
	for (int i = 0; i < nItemCount; i++) {
		// 4번째 열의 값을 가져와서 int로 변환하여 더함
		int value_in_column_4 = _ttoi(temp_list.GetItemText(i, 4));

		total_money += value_in_column_4;

	}

	SetDlgItemInt(IDC_TOTAL_MONEY, total_money);
}


void CLIENT_CAFE_DLG::OnBnClickedButtonMenuMod()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();
	POSITION pos = temp_list.GetFirstSelectedItemPosition();
	int index = temp_list.GetNextSelectedItem(pos);
	if (index == -1)
	{
		return;
	}

	CString pre_total = temp_list.GetItemText(index, 4);
	int pre_money = _ttoi(pre_total);

	LVITEM li = { 0 };
	li.iItem = index;
	li.iSubItem = 0;
	wchar_t nbuf[256] = TEXT("");
	li.mask = LVIF_TEXT;
	li.pszText = nbuf;
	li.cchTextMax = 256;

	temp_list.GetItem(&li);

	wchar_t my_place[256];
	GetDlgItemText(IDC_EDIT_SPIN2, edit_spin);
	wsprintf(my_place, TEXT("%s"), edit_spin);

	temp_list.SetItemText(index, 3, my_place);
	int quantity = _wtoi(my_place);
	CString price = temp_list.GetItemText(index, 2);
	int total = quantity * _wtoi(price);
	wchar_t total1[256];
	wsprintf(total1, TEXT("%d"), total);
	temp_list.SetItemText(index, 4, total1);

	//==============
	int nItemCount = temp_list.GetItemCount();
	total_money = 0;
	for (int i = 0; i < nItemCount; i++) {
		// 4번째 열의 값을 가져와서 int로 변환하여 더함
		int value_in_column_4 = _ttoi(temp_list.GetItemText(i, 4));

		total_money += value_in_column_4;

	}

	SetDlgItemInt(IDC_TOTAL_MONEY, total_money);
	//------------
		//ICE/HOT
	int state_radio1 = drink_ice_1.GetCheck();
	int state_radio2 = drink_hot_1.GetCheck();
	CString ice_hot;
	if (state_radio1)
	{
		ice_hot = _T("ICE");
	}
	else if (state_radio2)
	{
		ice_hot = _T("HOT");
	}
	temp_list.SetItemText(index, 1, ice_hot);

}


void CLIENT_CAFE_DLG::OnBnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	LPCTSTR lpctstr;
	UpdateData(TRUE);
	m_edit_send.GetWindowTextW(str);
	lpctstr = (LPCTSTR)str;
	//m_ClientSocket.Send((LPVOID)(LPCTSTR)str,str.GetLength() *2);
	m_ClientSocket.Send(lpctstr, lstrlen(lpctstr) * 2);
	m_edit_send.SetWindowTextW(_T(""));
	UpdateData(FALSE);
	//m_ClientSocket.Close();

}
LRESULT CLIENT_CAFE_DLG::OnClientRecv(WPARAM wParam, LPARAM lParam)
{
	LPCTSTR lpszStr = (LPCTSTR)lParam;
	if (_tcsstr(lpszStr, _T("[구매목록]")) != NULL)
	{
		// [구매목록] 메시지인 경우, 무시하고 바로 반환
		return 0;
	}

	// [구매목록]이 아닌 메시지만 추가합니다.
	m_list_msg.AddString(lpszStr);
	m_list_msg.SetCurSel(m_list_msg.GetCount() - 1);

	return 0;
}
