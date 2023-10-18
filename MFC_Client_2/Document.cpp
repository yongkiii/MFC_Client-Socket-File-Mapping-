#include "pch.h"
#include "Document.h"

Document* Document::singleton;

Document* Document::GetSingleton()
{
	if (singleton == 0)
	{
		singleton = new Document();
	}
	return singleton;
}

int  Document::GetLastSN_P1()
{
	return Info::GetLastSN() + 1;
}

void Document::RegInfo(int no, CString id, int point, CString pro_name, CString ice_hot, int money, int num, int hap, CString date)
{
	Info* info = new Info(id, point, pro_name, ice_hot, money, num, hap, date);
	infoes.push_back(info);
	HIter seek = handles.begin();
	HIter end = handles.end();
	int sn = GetLastSN_P1();
}

void Document::RegHandle(HWND hWnd)
{
	handles.push_back(hWnd);

}


Document::Document()
{

}