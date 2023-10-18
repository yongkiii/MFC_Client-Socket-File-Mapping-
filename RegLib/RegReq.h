#pragma once
#include <Windows.h>
#include "..\PacketLib2\\Packet2.h"
#include "..\common\\ehdef.h"

#ifdef aaareg
#define REG_DLL	__declspec(dllexport)
#else
#define REG_DLL	__declspec(dllimport)
#endif

class REG_DLL RegReq
{
	char id[MAX_ID_LEN];
	char pw[MAX_PW_LEN];
	char name[MAX_NAME_LEN];
	char phone[MAX_PHONE_LEN];
	char birth[MAX_BIRTH_LEN];
	char addr[MAX_ADDR_LEN];

public:
	RegReq(const char* id, const char* pw, const char* name, const char* phone, const char* birth, const char* addr);
	RegReq(Packet2* pac);
	void Send(HANDLE hFile);
	const char* GetID();
	const char* GetPW();
	const char* GetName();
	const char* GetPhone();
	const char* GetBirth();
	const char* GetAddr();
};

