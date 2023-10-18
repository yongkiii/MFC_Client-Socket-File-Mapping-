#pragma once
#include <Windows.h>
#include "..\PacketLib2\Packet2.h"
#include "..\\common\\\ehdef.h"
#ifdef aaareg
#define LOG_DLL	__declspec(dllexport)
#else
#define LOG_DLL	__declspec(dllimport)
#endif

class LOG_DLL LoginReq
{
	char id[MAX_ID_LEN];
	char pw[MAX_PW_LEN];
public:
	LoginReq(const char* id, const char* pw);
	LoginReq(Packet2* ep);//�����ϴ� �κ�
	void Send(HANDLE hFile);//���ۺκ�
	//�ش� �����͵� Ȯ�� �κ�

	const char* GetID();
	const char* GetPW();
};



