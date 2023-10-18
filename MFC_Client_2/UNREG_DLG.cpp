// UNREG_DLG.cpp: 구현 파일
//

#include "pch.h"
#include "MFC_Client_2.h"
#include "afxdialogex.h"
#include "UNREG_DLG.h"
#include <afxdb.h>

#include "..\\PacketLib2\\Packet2.h"
#include "..\\RegLib\\UnRegReq.h"
#include "..\\common\\ehdef.h"

#pragma comment(lib,"..\\x64\\Debug\\PacketLib2.lib")
#pragma comment(lib,"..\\x64\\Debug\\RegLib.lib")

// UNREG_DLG 대화 상자

IMPLEMENT_DYNAMIC(UNREG_DLG, CDialogEx)

UNREG_DLG::UNREG_DLG(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_UNREG, pParent)
	, UNREG_ID(_T(""))
	, UNREG_PW(_T(""))
	, UNREG_PW_OK(_T(""))
{

}

UNREG_DLG::~UNREG_DLG()
{
}

void UNREG_DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, UNREG_ID);
	DDX_Text(pDX, IDC_EDIT2, UNREG_PW);
	DDX_Text(pDX, IDC_EDIT3, UNREG_PW_OK);
}


BEGIN_MESSAGE_MAP(UNREG_DLG, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_UNREG, &UNREG_DLG::OnBnClickedButtonUnreg)
END_MESSAGE_MAP()


// UNREG_DLG 메시지 처리기


void UNREG_DLG::OnBnClickedButtonUnreg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_EDIT1, UNREG_ID);
	GetDlgItemText(IDC_EDIT2, UNREG_PW);
	GetDlgItemText(IDC_EDIT3, UNREG_PW_OK);


	if (UNREG_PW != UNREG_PW_OK)
	{
		MessageBox(TEXT("비밀번호가 달라!"));
		return;
	}

	char id[MAX_ID_LEN] = "";
	char pw[MAX_PW_LEN] = "";

	CStringA cstrAID(UNREG_ID);
	CStringA cstrAPW(UNREG_PW);

	strcpy_s(id, MAX_ID_LEN, cstrAID);
	strcpy_s(pw, MAX_PW_LEN, cstrAPW);

	HANDLE hPipe = CreateFile(REG_PNAME, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE,
		0, OPEN_EXISTING, 0, 0);

	UnRegReq* urr = new UnRegReq(id, pw);
	urr->Send(hPipe);
	delete urr;
	CloseHandle(hPipe);
	MessageBox(TEXT("탈출!"));


	CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=DESKTOP-MVM6023; uid = scott;PWD=tiger"));

	if (re == FALSE)
	{
		return;
	}

	CRecordset rs(&db);
	CString str;

	str.Format(TEXT("delete from UUSER where U_ID='%s'"), UNREG_ID);

	wchar_t query_str[100] = TEXT("");
	wsprintf(query_str, str);
	MessageBox(TEXT("회원 탈퇴 성공"));


	db.ExecuteSQL(query_str);
	db.Close();

}
