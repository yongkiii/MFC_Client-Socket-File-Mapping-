
// MFC_ClientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFC_Client_2.h"
#include "MFC_Client_2Dlg.h"
#include "afxdialogex.h"

#include "REG_DLG.h"
#include "UNREG_DLG.h"
#include "CLIENT_CAFE_DLG.h"
#include "My_Info.h"

#include <afxdb.h>

#include "..\\LogLib\\LoginReq.h"
#include "..\\LogLib\\LoginRes.h"
#include "..\\common\\ehdef.h"

#pragma comment(lib,"..\\x64\\Debug\\PacketLib2.lib")
#pragma comment(lib,"..\\x64\\Debug\\LogLib.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCClient2Dlg 대화 상자



CMFCClient2Dlg::CMFCClient2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAIN, pParent)
	, LOGIN_ID(_T(""))
	, LOGIN_PW(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCClient2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, LOGIN_ID);
	DDX_Text(pDX, IDC_EDIT2, LOGIN_PW);
}

BEGIN_MESSAGE_MAP(CMFCClient2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_REG, &CMFCClient2Dlg::OnBnClickedButtonReg)
	ON_BN_CLICKED(IDC_BUTTON_UNREG, &CMFCClient2Dlg::OnBnClickedButtonUnreg)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CMFCClient2Dlg::OnBnClickedButtonLogin)
END_MESSAGE_MAP()


// CMFCClient2Dlg 메시지 처리기

BOOL CMFCClient2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCClient2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCClient2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		CDC MemDC;
		CBitmap bmp;

		CRect rct;
		this->GetClientRect(&rct);

		// Then load the bitmap to the memory.
		MemDC.CreateCompatibleDC(&dc);
		bmp.LoadBitmap(IDB_BITMAP8);
		MemDC.SelectObject(&bmp);

		// dialog surface.
		dc.BitBlt(0, 0, rct.Width(), rct.Height(), &MemDC, 0, 0, SRCCOPY);
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCClient2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCClient2Dlg::OnBnClickedButtonReg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	REG_DLG* reg = new REG_DLG();
	reg->Create(IDD_REG);
	reg->ShowWindow(SW_SHOW);
}


void CMFCClient2Dlg::OnBnClickedButtonUnreg()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UNREG_DLG* unreg = new UNREG_DLG();
	unreg->Create(IDD_UNREG);
	unreg->ShowWindow(SW_SHOW);
}


void CMFCClient2Dlg::OnBnClickedButtonLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData();

	My_Info* mi = My_Info::GetInstance();


	GetDlgItemText(IDC_EDIT1, LOGIN_ID);
	GetDlgItemText(IDC_EDIT2, LOGIN_PW);

	char id[MAX_ID_LEN] = "";
	char pw[MAX_PW_LEN] = "";

	CStringA cstrAID(LOGIN_ID);
	CStringA cstrAPW(LOGIN_PW);

	const wchar_t* myid = LOGIN_ID.GetString();
	const wchar_t* mypw = LOGIN_PW.GetString();

	strcpy_s(id, MAX_ID_LEN, cstrAID);
	strcpy_s(pw, MAX_PW_LEN, cstrAPW);

	HANDLE hPipe = CreateFile(REG_PNAME, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE,
		0, OPEN_EXISTING, 0, 0);

	LoginReq* lr = new LoginReq(id, pw);
	lr->Send(hPipe);
	delete lr;
	Packet2* ep = new Packet2(hPipe);
	LoginRes* lres = new LoginRes(ep);//로긴 요청 결과 수신
	int result = lres->GetResult();
	if (result == LOGIN_RES_OK)
	{
		MessageBox(TEXT("로그인 성공"));

		mi->Set_id(myid);
		mi->Set_pw(mypw);


		CLIENT_CAFE_DLG* cafe = new CLIENT_CAFE_DLG();
		cafe->Create(IDD_CLIENT_CAFE);
		cafe->ShowWindow(SW_SHOW);
	}
	else
	{
		switch (result)
		{
		case LOGIN_RES_ALR: MessageBox(TEXT("이미 로긴 중입니다.\n"));  break;
		case LOGIN_RES_NOC: MessageBox(TEXT("비밀 번호가 다릅니다.\n"));  break;
		case LOGIN_RES_NOI: MessageBox(TEXT("아이디가 없습니다.\n")); break;
		default: MessageBox(TEXT("암튼... 로긴은 못했습니다.\n")); break;
		}
	}
	delete lres;
	CloseHandle(hPipe);
}
//void CMFCClient2Dlg::OnBnClickedButtonLogin()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	UpdateData();
//
//	MessageBox(TEXT("로그인 성공"));
//	CLIENT_CAFE_DLG* cafe = new CLIENT_CAFE_DLG();
//	cafe->Create(IDD_CLIENT_CAFE);
//	cafe->ShowWindow(SW_SHOW);
//
//
//}