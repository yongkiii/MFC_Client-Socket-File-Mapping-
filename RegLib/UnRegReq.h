#pragma once
#include <Windows.h>
#include "..\\common\ehdef.h"
#include "..\\PacketLib2\Packet2.h"
#ifdef aaareg
#define REG_DLL	__declspec(dllexport)
#else
#define REG_DLL	__declspec(dllimport)
#endif

class REG_DLL UnRegReq
{
	char id[MAX_ID_LEN];
	char pw[MAX_PW_LEN];
public:
	UnRegReq(const char* id, const char* pw);
	UnRegReq(Packet2* pack);
	void Send(HANDLE hFile);
	const char* GetID();
	const char* GetPW();
};

