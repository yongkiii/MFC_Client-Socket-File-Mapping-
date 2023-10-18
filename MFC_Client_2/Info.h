#pragma once
class Info
{
	//buydata.Format(_T("[구매목록] no : %d, user id : %s, point : %d, product name: %s, ice/hot: %s, money: %d, buy num: %d, hap money: %d, date: %s"),
	//i, ID, D_POINT, D_PRO_NAME, D_PRO_ICE_HOT, D_PRO_MONEY, D_BUY_NUM, D_HAP_MONEY, currentDateStr);

	//CString no;
	CString id;
	int point;
	CString pro_name;
	CString ice_hot;
	int money;
	int num;
	int hap;
	CString date;
	static int last_sn;
	const int sn;

public:
	Info(CString id, int point, CString pro_name, CString ice_hot, int money, int num, int hap, CString date);
	CString Get_id();
	int Get_point();
	CString Get_pro_name();
	CString Get_ice_hot();
	int Get_money();
	int Get_num();
	int Get_hap();
	CString Get_date();

	int GetSN();
	void SetSN(int sn);

	static int GetLastSN();

	Info* info = nullptr;

};

