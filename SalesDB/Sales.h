#pragma once
#ifdef SALEASDFASDFQWERQWER1234
#define DLL_CLASS __declspec(dllexport)
#else
#define DLL_CLASS __declspec(dllimport)
#endif
class DLL_CLASS Sales
{
	CString S_ID;
	int S_POINT;
	CString S_PRO_NAME;
	CString S_ICE_HOT;
	int S_MONEY;
	int S_NUM;
	int S_HAP_MONEY;
	CString S_DATE;

public:
	Sales(CString S_ID, int S_POINT,CString S_PRO_NAME,CString S_ICE_HOT,int S_MONEY,int S_NUM,int S_HAP_MONEY, CString S_DATE);
	CString GetSID();
	CString GetSPointStr();
	CString GetSProName();
	CString GetSIceHot();
	CString GetSMoneyStr();
	CString GetSNumStr();
	CString GetSHapMoneyStr();
	int GetSHapMoney();
	CString GetSDate();
};