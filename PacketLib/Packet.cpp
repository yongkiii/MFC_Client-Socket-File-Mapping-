#define aaapacket
#include "Packet.h"
#pragma comment(lib,"ws2_32")
// 메시지 아이디(msgid)를 입력받아 객체를 초기화
Packet::Packet(int msgid)
{
	mh.msgid = msgid;
	mh.bdlen = 0;
}


//Packet::Packet(HANDLE hFile)
//{
//	DWORD dw;
//	ReadFile(hFile, &mh, sizeof(MsgHead), &dw, 0);
//	ReadFile(hFile, body, mh.bdlen, &dw, 0);
//	offset = body;
//}

//데이터를 패킷 바디에 캡슐화(추가)
//입력된 데이터(data)와 길이(dlen)를 패킷 바디(body)에 추가하고, 바디 길이를 업데이트
void Packet::Capsulate(void* data, int dlen)
{
	memcpy_s(body + mh.bdlen, MAX_BODY_LEN - mh.bdlen, data, dlen);
	mh.bdlen += dlen;
}

// 데이터를 디캡슐화(추출)
void Packet::Decapsulate(void* base, int blen)
{
	if ((offset + blen - body) > mh.bdlen)
	{
		return;
	}
	//base에 디캡슐화된 데이터를 복사
	//바디 데이터를 가리키는 offset를 업데이트
	memcpy_s(base, blen, offset, blen);
	offset += blen;
}

// 패킷을 파일에 시리얼라이즈(저장)
//메시지 헤더(mh)와 바디 데이터(body)를 파일에 씀
//void Packet::Serialize(HANDLE hFile)
//{
//	DWORD dw;
//	WriteFile(hFile, &mh, sizeof(MsgHead), &dw, 0);
//	WriteFile(hFile, body, mh.bdlen, &dw, 0);
//}

//패킷의 메시지 아이디(msgid)를 반환
//어떤 종류의 메시지를 담고 있는지 확인하기 위해
int Packet::GetMsgID()
{
	return mh.msgid;
}

//소켓 통신
Packet::Packet(SOCKET sock)
{
	recv(sock, (char*)&mh, sizeof(MsgHead), 0);
	recv(sock, body, mh.bdlen, 0);
	offset = body;
}

void Packet::Send(SOCKET sock)
{
	send(sock, (char*)&mh, sizeof(MsgHead), 0);
	send(sock, body, mh.bdlen, 0);
}