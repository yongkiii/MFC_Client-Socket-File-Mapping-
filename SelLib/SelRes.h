
#pragma once

#include "..\\PacketLib\Packet.h"
#ifdef aaasel
#define SEL_DLL	__declspec(dllexport)
#else
#define SEL_DLL	__declspec(dllimport)
#endif

class SEL_DLL SelRes
{
	int result;
public:
	SelRes(int result);
	SelRes(Packet* ep);
	//void Send(HANDLE hFile);
	int GetResult();
	void Send(SOCKET sock);
};

