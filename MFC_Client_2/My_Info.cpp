#include "pch.h"
#include "My_Info.h"

My_Info* My_Info::info = NULL;

My_Info::My_Info()
{
	wsprintf(id, TEXT(""));
	wsprintf(pw, TEXT(""));
}

My_Info* My_Info::GetInstance()
{
	if (info == NULL)
	{
		info = new My_Info();
	}
	return info;
}

void My_Info::Set_id(const wchar_t _id[256])
{
	wsprintf(id, TEXT("%s"), _id);
}
void My_Info::Set_pw(const wchar_t _pw[256])
{
	wsprintf(pw, TEXT("%s"), _pw);
}
wchar_t* My_Info::Get_id()
{
	return id;
}
wchar_t* My_Info::Get_pw()
{
	return pw;
}