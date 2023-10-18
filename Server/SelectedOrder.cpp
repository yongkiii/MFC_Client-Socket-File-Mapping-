#include "pch.h"
#include "SelectedOrder.h"

SelectedOrder* SelectedOrder::order = NULL;

SelectedOrder::SelectedOrder()
{
	wsprintf(SeletedID, TEXT(""));
	wsprintf(SeletedDATE, TEXT(""));
}

SelectedOrder* SelectedOrder::GetInstance()
{
	if (order == NULL)
	{
		order = new SelectedOrder();
	}
	return order;
}

void SelectedOrder::Set_SeletedID(const wchar_t _SeletedID[256])
{
	wsprintf(SeletedID, TEXT("%s"), _SeletedID);
}
void SelectedOrder::Set_SeletedDATE(const wchar_t _SeletedDATE[256])
{
	wsprintf(SeletedDATE, TEXT("%s"), _SeletedDATE);
}
void SelectedOrder :: Set_SeletedProNAME(const wchar_t _SeletedProNAME[256])
{
	wsprintf(SeletedProNAME, TEXT("%s"), _SeletedProNAME);

}

wchar_t* SelectedOrder::Get_SeletedID()
{
	return SeletedID;
}
wchar_t* SelectedOrder::Get_SeletedDATE()
{
	return SeletedDATE;
}
wchar_t* SelectedOrder::Get_SeletedProNAME()
{
	return SeletedProNAME;
}