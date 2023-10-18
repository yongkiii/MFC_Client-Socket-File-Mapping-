// REG_DLG.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_Client_2.h"
#include "afxdialogex.h"
#include "REG_DLG.h"

#include <afxdb.h>

#include "..\\PacketLib2\\Packet2.h"
#include "..\\RegLib\\RegReq.h"
#include "..\\RegLib\\RegRes.h"
#include "..\\common\\ehdef.h"

#pragma comment(lib,"..\\x64\\Debug\\PacketLib2.lib")
#pragma comment(lib,"..\\x64\\Debug\\RegLib.lib")

// REG_DLG 대화 상자

IMPLEMENT_DYNAMIC(REG_DLG, CDialogEx)

REG_DLG::REG_DLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REG, pParent)
	, REG_ID(_T(""))
	, REG_DATE(COleDateTime::GetCurrentTime())
	, REG_ADDR(_T(""))
	, REG_PHONE(_T(""))
{

}

REG_DLG::~REG_DLG()
{
}

void REG_DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, REG_ID);
	DDX_Text(pDX, IDC_EDIT2, REG_PW);
	DDX_Text(pDX, IDC_EDIT3, REG_PW_OK);
	DDX_Text(pDX, IDC_EDIT4, REG_NAME);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, REG_DATE_CON);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, REG_DATE);
	DDX_Text(pDX, IDC_EDIT6, REG_ADDR);
	DDX_Text(pDX, IDC_EDIT7, REG_PHONE);
}


BEGIN_MESSAGE_MAP(REG_DLG, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REG, &REG_DLG::OnBnClickedButtonReg)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &REG_DLG::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// REG_DLG 메시지 처리기


void REG_DLG::OnBnClickedButtonReg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=MFC; uid = scott;PWD=tiger"));

	if (re == FALSE)
	{
		return;
	}
	GetDlgItemText(IDC_EDIT1, REG_ID);
	GetDlgItemText(IDC_EDIT2, REG_PW);
	GetDlgItemText(IDC_EDIT3, REG_PW_OK);
	GetDlgItemText(IDC_EDIT4, REG_NAME);
	CString date2Str = REG_DATE.Format(_T("%Y-%m-%d"));
	GetDlgItemText(IDC_EDIT6, REG_ADDR);
	GetDlgItemText(IDC_EDIT7, REG_PHONE);

	if (REG_PW != REG_PW_OK)
	{
		MessageBox(TEXT("비밀번호가 달라!"));
		return;
	}


	char id[MAX_ID_LEN] = "";
	char pw[MAX_PW_LEN] = "";
	char name[MAX_NAME_LEN] = "";
	char phone[MAX_PHONE_LEN] = "";
	char birth[MAX_BIRTH_LEN] = "";
	char addr[MAX_ADDR_LEN] = "";

	CStringA cstrAID(REG_ID);
	CStringA cstrAPW(REG_PW);
	CStringA cstrAName(REG_PW_OK);
	CStringA cstrAPhone(REG_PHONE);
	CStringA cstrABirth(date2Str);
	CStringA cstrAAddr(REG_ADDR);

	strcpy_s(id, MAX_ID_LEN, cstrAID);
	strcpy_s(pw, MAX_PW_LEN, cstrAPW);
	strcpy_s(name, MAX_NAME_LEN, cstrAName);
	strcpy_s(phone, MAX_PHONE_LEN, cstrAPhone);
	strcpy_s(birth, MAX_BIRTH_LEN, cstrABirth);
	strcpy_s(addr, MAX_ADDR_LEN, cstrAAddr);


	HANDLE hPipe = CreateFile(REG_PNAME, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE,
		0, OPEN_EXISTING, 0, 0);

	//reg_id reg_password reg_passwordcheck reg_name reg_birthdate reg_address
	RegReq* rr = new RegReq(id, pw, name, phone, birth, addr);
	rr->Send(hPipe);
	delete rr;
	Packet2* ep = new Packet2(hPipe);
	RegRes* rres = new RegRes(ep);//가입 요청 결과 수신
	if (rres->GetResult() == REG_RES_OK)
	{
		printf("가입 성공\n");
	}
	else
	{
		printf("가입 실패\n");
	}
	delete rres;
	CloseHandle(hPipe);
	OnCancel();

	//=====
	wchar_t query_str[256] = TEXT("");
	wsprintf(query_str, TEXT("insert into UUSER (U_ID, U_PW, U_NAME, U_BIRTH, U_ADDR, U_PHONE, U_POINT ) values ('%s', '%s', '%s', '%s', '%s', '%s', %d)"), REG_ID, REG_PW, REG_NAME, date2Str, REG_ADDR, REG_PHONE,1000);
	db.ExecuteSQL(query_str);
	db.Close();
}


void REG_DLG::OnBnClickedButtonCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
