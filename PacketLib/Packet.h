#pragma once
#include <WinSock2.h>
#include <Windows.h>
#ifdef aaapacket
#define PACKET_DLL __declspec(dllexport)
#else
#define PACKET_DLL __declspec(dllimport)
#endif

struct PACKET_DLL MsgHead
{
	//packet
	int msgid;
	int bdlen;

};

#define MAX_BODY_LEN 9176

class PACKET_DLL Packet
{
	MsgHead mh;
	char body[MAX_BODY_LEN];
	char* offset;

public:
	Packet(int msgid);
	//Packet(HANDLE hFile);
	Packet(SOCKET sock);
	void Capsulate(void* data, int dlen);
	void Decapsulate(void* base, int blen);
	//void Serialize(HANDLE fFile);
	void Send(SOCKET sock);
	int GetMsgID();
};
