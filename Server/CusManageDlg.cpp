// CusManageDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Server.h"
#include "afxdialogex.h"
#include "CusManageDlg.h"


// CusManageDlg 대화 상자

IMPLEMENT_DYNAMIC(CusManageDlg, CDialogEx)

CusManageDlg::CusManageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CUSMANAGE_DIALOG, pParent)
{

}

CusManageDlg::~CusManageDlg()
{
}

void CusManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CusManageDlg, CDialogEx)
END_MESSAGE_MAP()


// CusManageDlg 메시지 처리기
