#pragma once
#include "afxdialogex.h"
#include "CClientSocket.h"

// CLIENT_CAFE_DLG 대화 상자

class CLIENT_CAFE_DLG : public CDialogEx
{

	DECLARE_DYNAMIC(CLIENT_CAFE_DLG)
		int spin_value = 0;
	int total_money = 0;
	int final_point = 0;
private:
	CClientSocket m_ClientSocket;
	//SOCKET m_ClientSocket;

public:
	CLIENT_CAFE_DLG(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CLIENT_CAFE_DLG();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENT_CAFE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonLogout();
	//라디오 아이스
	CButton drink_ice_1;
	CButton drink_hot_1;

	CButton drink_1;
	CButton drink_2;
	CButton drink_3;
	CButton drink_4;
	CButton drink_5;
	CButton drink_6;

	CListCtrl temp_list;
	virtual BOOL OnInitDialog();

public:
	//void AddedBook(Cafe* cafe);

	afx_msg void OnBnClickedButtonCafe1();
	afx_msg void OnBnClickedButtonCafe2();
	afx_msg void OnBnClickedButtonCafe3();
	afx_msg void OnBnClickedButtonCafe4();
	afx_msg void OnBnClickedButtonCafe5();
	afx_msg void OnBnClickedButtonCafe6();

public:
	void SetSpinValue(int spin_value);
	afx_msg void OnDeltaposSpinQuantity2(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl point_list;

	afx_msg void OnBnClickedButtonPoint();

public:
	CString u_id;
	CString u_name;
	CString point;
	afx_msg void OnBnClickedButton1Buy();
	afx_msg void OnBnClickedButtonMenuDel();
	afx_msg void OnBnClickedButtonMenuMod();
	CString edit_spin;


	CString message;
	afx_msg void OnBnClickedButtonSend();
	CEdit m_edit_send;
	CListBox m_list_msg;

	SOCKET Connect();


protected:
	afx_msg LRESULT OnClientRecv(WPARAM wParam, LPARAM lParam);  //사용자 메시지 함수 추가

};