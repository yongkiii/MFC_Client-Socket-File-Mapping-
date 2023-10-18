#pragma once
#include <Windows.h>
#include "..\\PacketLib2\Packet2.h"

#ifdef aaareg
#define REG_DLL	__declspec(dllexport)
#else
#define REG_DLL	__declspec(dllimport)
#endif

class REG_DLL RegRes
{
	int result;
public:
	RegRes(int result);
	RegRes(Packet2* ep);
	void Send(HANDLE hFile);
	int GetResult();
};

