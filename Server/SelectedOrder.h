#pragma once
class SelectedOrder
{
private:
	static SelectedOrder* order;
private:
	SelectedOrder();

private:
	wchar_t SeletedID[256];
	wchar_t SeletedDATE[256];
	wchar_t SeletedProNAME[256];
public:
	static SelectedOrder* GetInstance();

	void Set_SeletedID(const wchar_t SeletedID[256]);
	void Set_SeletedDATE(const wchar_t SeletedID[256]);
	void Set_SeletedProNAME(const wchar_t SeletedProNAME[256]);
	wchar_t* Get_SeletedID();
	wchar_t* Get_SeletedDATE();
	wchar_t* Get_SeletedProNAME();

};

