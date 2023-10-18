#pragma once
#include <map>
#include "Sales.h"

using std::map;
typedef map<int, Sales*> SalesMap;
typedef SalesMap::iterator SIter;

class DLL_CLASS SalesManager
{
	CString constr;
public:
	void SetConnStr(CString constr);
	void SelectAll(SalesMap& sm);
	void AddSales(CString S_ID, int S_POINT, CString S_PRO_NAME, CString S_ICE_HOT, int S_MONEY, int S_NUM, int S_HAP_MONEY, CString S_DATE);
	void RemoveSales(CString S_ID, CString S_DATE);
	void Removeitem(CString S_ID, CString S_DATE, CString S_PRO_NAME);
	void UpdateSales(CString S_ID, int S_POINT, CString S_PRO_NAME, CString S_ICE_HOT, int S_MONEY, int S_NUM, int S_HAP_MONEY, CString S_DATE);
	void UpdateItemCount(CString S_ID, CString S_DATE, CString S_PRO_NAME, int S_NUM);
};