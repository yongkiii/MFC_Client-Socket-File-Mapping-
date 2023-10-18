#pragma once
#include <Windows.h>

#ifdef packetpipe123123
#define PACKET_DLL2 __declspec(dllexport)
#else
#define PACKET_DLL2 __declspec(dllimport)
#endif

struct PACKET_DLL2 MsgHead2
{
	//packet
	int msgid;
	int bdlen;

};

#define MAX_BODY_LEN 4088

class PACKET_DLL2 Packet2
{
	MsgHead2 mh2;
	char body[MAX_BODY_LEN];
	char* offset;

public:
	Packet2(int msgid);
	Packet2(HANDLE hFile);

	void Capsulate(void* data, int dlen);
	void Decapsulate(void* base, int blen);
	void Serialize(HANDLE fFile);

	int GetMsgID();
};
