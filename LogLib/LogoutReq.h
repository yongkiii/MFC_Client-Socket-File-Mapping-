#pragma once
#include <Windows.h>
#include "..\PacketLib2\Packet2.h"
#include "..\\common\\\ehdef.h"
#ifdef aaareg
#define LOG_DLL	__declspec(dllexport)
#else
#define LOG_DLL	__declspec(dllimport)
#endif

class LOG_DLL LogoutReq
{
	char id[MAX_ID_LEN];
	char pw[MAX_PW_LEN];
public:
	LogoutReq(const char* id, const char* pw);
	LogoutReq(Packet2* pac);	//수신하는 부분
	void Send(HANDLE hFile);//전송부분

	//해당 데이터들 확인 부분
	const char* GetID();
	const char* GetPW();
};
