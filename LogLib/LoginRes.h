#pragma once
#include <Windows.h>
#include "..\PacketLib2\Packet2.h"

#ifdef aaareg
#define LOG_DLL	__declspec(dllexport)
#else
#define LOG_DLL	__declspec(dllimport)
#endif

class LOG_DLL LoginRes
{
	int result;
public:
	LoginRes(int result);
	LoginRes(Packet2* ep);	//수신하는 부분
	void Send(HANDLE hFile);//전송부분
	int GetResult();
};

