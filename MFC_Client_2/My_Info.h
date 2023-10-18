#pragma once
class My_Info
{
private:
	static My_Info* info;
private:
	My_Info();

private:
	wchar_t id[256];
	wchar_t pw[256];
public:
	static My_Info* GetInstance();

	void Set_id(const wchar_t _id[256]);
	void Set_pw(const wchar_t _pw[256]);
	wchar_t* Get_id();
	wchar_t* Get_pw();

};

