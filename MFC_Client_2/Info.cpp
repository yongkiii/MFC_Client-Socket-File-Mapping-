#include "pch.h"
#include "Info.h"

int Info::last_sn;


Info::Info(CString id, int point, CString pro_name, CString ice_hot, int money, int num, int hap, CString date)
	:sn(last_sn + 1)
{
	last_sn++;
	this->id = id;
	this->point = point;
	this->pro_name = pro_name;
	this->ice_hot = ice_hot;
	this->money = money;
	this->num = num;
	this->hap = hap;
	this->date = date;
}

CString Info::Get_id()
{
	return id;
}

int Info::Get_point()
{
	return point;
}

CString Info::Get_pro_name()
{
	return pro_name;
}  

CString Info::Get_ice_hot()
{
	return ice_hot;
}

int Info::Get_money()
{
	return money;
}

int Info::Get_num()
{
	return num;
}

int Info::Get_hap()
{
	return hap;
}

CString Info::Get_date()
{
	return date;
}

int Info::GetSN()
{
	return sn;
}

void Info::SetSN(int sn)
{
	this->last_sn = sn;

}

int Info::GetLastSN()
{
	return last_sn;
}
