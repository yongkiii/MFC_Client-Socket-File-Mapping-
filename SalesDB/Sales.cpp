#include "pch.h"
#define SALEASDFASDFQWERQWER1234
#include "Sales.h"
Sales::Sales(CString S_ID, int S_POINT, CString S_PRO_NAME, CString S_ICE_HOT, int S_MONEY, int S_NUM, int S_HAP_MONEY, CString S_DATE)
{
	this->S_ID = S_ID;
	this->S_POINT = S_POINT;
	this->S_PRO_NAME = S_PRO_NAME;
	this->S_ICE_HOT = S_ICE_HOT;
	this->S_MONEY = S_MONEY;
	this->S_NUM = S_NUM;
	this->S_HAP_MONEY = S_HAP_MONEY;
	this->S_DATE = S_DATE;
}
CString Sales::GetSID()
{
	return S_ID;
}
CString Sales::GetSPointStr()
{
	wchar_t buf[256];
	wsprintf(buf, TEXT("%d"), S_POINT);
	return buf;
}
CString Sales::GetSProName()
{
	return S_PRO_NAME;
}
CString Sales::GetSIceHot()
{
	return S_ICE_HOT;
}
CString Sales::GetSMoneyStr()
{
	wchar_t buf[256];
	wsprintf(buf, TEXT("%d"), S_MONEY);
	return buf;
}
CString Sales::GetSNumStr()
{
	wchar_t buf[256];
	wsprintf(buf, TEXT("%d"), S_NUM);
	return buf;
}
CString Sales::GetSHapMoneyStr()
{
	wchar_t buf[256];
	wsprintf(buf, TEXT("%d"), S_HAP_MONEY);
	return buf;
}
int Sales::GetSHapMoney()
{
	return S_HAP_MONEY;
}
CString Sales::GetSDate()
{
	return S_DATE;
}
