
#include "pch.h"
#define SALEASDFASDFQWERQWER1234
#include "SalesManager.h"
#include "..\\DBControl\\DBConnect.h"
#pragma comment(lib,"../x64/Debug/DBControl.lib")
#include <afxdb.h>

void SalesManager::SetConnStr(CString constr)
{
	this->constr = constr;
}

void SalesManager::SelectAll(SalesMap& sm)
{
	CString S_ID;
	CString S_POINT_STR;
	int S_POINT;
	CString S_PRO_NAME;
	CString S_ICE_HOT;
	CString S_MONEY_STR;
	int S_MONEY;
	CString S_NUM_STR;
	int S_NUM;
	CString S_HAP_MONEY_STR;
	int S_HAP_MONEY;
	CString S_DATE;

	DBConnect* dbc = DBConnect::GetInstance(constr);
	CRecordset* rs = dbc->Select();

	rs->Open(CRecordset::forwardOnly, TEXT("select *from sel"));
	int index = 0;
	while (!rs->IsEOF())
	{
		rs->GetFieldValue((short)0, S_ID);
		rs->GetFieldValue((short)1, S_POINT_STR);
		S_POINT = _wtoi(S_POINT_STR);
		rs->GetFieldValue((short)2, S_PRO_NAME);
		rs->GetFieldValue((short)3, S_ICE_HOT);
		rs->GetFieldValue((short)4, S_MONEY_STR);
		S_MONEY = _wtoi(S_MONEY_STR);
		rs->GetFieldValue((short)5, S_NUM_STR);
		S_NUM = _wtoi(S_NUM_STR);
		rs->GetFieldValue((short)6, S_HAP_MONEY_STR);
		S_HAP_MONEY = _wtoi(S_HAP_MONEY_STR);
		rs->GetFieldValue((short)7, S_DATE);


		sm[index] = new Sales(S_ID, S_POINT, S_PRO_NAME, S_ICE_HOT, S_MONEY, S_NUM, S_HAP_MONEY, S_DATE);
		index++;
		rs->MoveNext();
	}
}

void SalesManager::AddSales(CString S_ID, int S_POINT, CString S_PRO_NAME, CString S_ICE_HOT, int S_MONEY, int S_NUM, int S_HAP_MONEY, CString S_DATE)
{

	DBConnect* dbc = DBConnect::GetInstance(constr);

	wchar_t query_str[512] = TEXT("");
	wsprintf(query_str, TEXT("insert into Sales(S_ID, S_POINT, S_PRO_NAME, S_ICE_HOT, S_MONEY, S_NUM, S_HAP_MONEY, S_DATE) values('%s',%d,'%s','%s',%d, %d, %d,'%s');"),
		S_ID, S_POINT, S_PRO_NAME, S_ICE_HOT, S_MONEY, S_NUM, S_HAP_MONEY, S_DATE);
	dbc->ExecuteQuery(query_str);
}
void SalesManager::RemoveSales(CString S_ID, CString S_DATE)
{

	DBConnect* dbc = DBConnect::GetInstance(constr);

	wchar_t query_str[200] = TEXT("");
	wsprintf(query_str, TEXT("delete from sel where S_ID='%s' and S_DATE='%s';"), S_ID, S_DATE);
	dbc->ExecuteQuery(query_str);
}
void SalesManager::Removeitem(CString S_ID, CString S_DATE, CString S_PRO_NAME)
{

	DBConnect* dbc = DBConnect::GetInstance(constr);

	wchar_t query_str[200] = TEXT("");
	wsprintf(query_str, TEXT("delete from sel where S_ID='%s' and S_DATE='%s';"), S_ID, S_DATE);
	dbc->ExecuteQuery(query_str);
}
void SalesManager::UpdateSales(CString S_ID, int S_POINT, CString S_PRO_NAME, CString S_ICE_HOT, int S_MONEY, int S_NUM, int S_HAP_MONEY, CString S_DATE)
{
	DBConnect* dbc = DBConnect::GetInstance(constr);


	wchar_t query_str[1000] = TEXT("");
	wsprintf(query_str, TEXT("update sel set S_POINT = %d, S_PRO_NAME = '%s', S_ICE_HOT = '%s',S_MONEY = %d,S_NUM=%d, S_HAP_MONEY=%d where S_ID='%s' and S_DATE='%s';"),
		S_POINT, S_PRO_NAME, S_ICE_HOT, S_MONEY, S_NUM, S_HAP_MONEY, S_ID, S_DATE);
	dbc->ExecuteQuery(query_str);
}
void SalesManager::UpdateItemCount(CString S_ID, CString S_DATE, CString S_PRO_NAME, int S_NUM)
{
	DBConnect* dbc = DBConnect::GetInstance(constr);
	wchar_t query_str[200] = TEXT("");
	if (S_NUM > 0) // 고칠려는 수량이 0보다 클 때만 실행하겠다.
	{
		wsprintf(query_str, TEXT("update sel set S_NUM=%d where S_ID='%s' and S_DATE = '%s' and S_PRO_NAME = '%s'"),
			S_NUM, S_ID, S_DATE, S_PRO_NAME);
		dbc->ExecuteQuery(query_str);
	}
}
