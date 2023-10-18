#pragma once
#include"Info.h"
#include<map>
#include<Windows.h>
#include<vector>

using std::vector;

typedef vector<Info*>CVec;
typedef CVec::iterator CIter;
typedef vector<HWND>HVec;
typedef HVec::iterator HIter;


//==============
using std::map;
typedef map<CString, Info*> MInfo;
typedef MInfo::iterator MIter;

class Document
{
	HVec handles;
	static Document* singleton;
	MInfo info_map;

public:
	static Document* GetSingleton();
	int GetLastSN_P1();					//���� �ֱ� �ο��� �����ȣ
	void RegInfo(int no, CString id, int point, CString pro_name, CString ice_hot, int money, int num, int hap, CString date);
	void RegHandle(HWND hWnd);
	CVec infoes;


	

private:
	Document();

};

