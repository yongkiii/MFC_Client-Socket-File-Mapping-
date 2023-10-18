#define aaapacket
#include "Packet.h"
#pragma comment(lib,"ws2_32")
// �޽��� ���̵�(msgid)�� �Է¹޾� ��ü�� �ʱ�ȭ
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

//�����͸� ��Ŷ �ٵ� ĸ��ȭ(�߰�)
//�Էµ� ������(data)�� ����(dlen)�� ��Ŷ �ٵ�(body)�� �߰��ϰ�, �ٵ� ���̸� ������Ʈ
void Packet::Capsulate(void* data, int dlen)
{
	memcpy_s(body + mh.bdlen, MAX_BODY_LEN - mh.bdlen, data, dlen);
	mh.bdlen += dlen;
}

// �����͸� ��ĸ��ȭ(����)
void Packet::Decapsulate(void* base, int blen)
{
	if ((offset + blen - body) > mh.bdlen)
	{
		return;
	}
	//base�� ��ĸ��ȭ�� �����͸� ����
	//�ٵ� �����͸� ����Ű�� offset�� ������Ʈ
	memcpy_s(base, blen, offset, blen);
	offset += blen;
}

// ��Ŷ�� ���Ͽ� �ø��������(����)
//�޽��� ���(mh)�� �ٵ� ������(body)�� ���Ͽ� ��
//void Packet::Serialize(HANDLE hFile)
//{
//	DWORD dw;
//	WriteFile(hFile, &mh, sizeof(MsgHead), &dw, 0);
//	WriteFile(hFile, body, mh.bdlen, &dw, 0);
//}

//��Ŷ�� �޽��� ���̵�(msgid)�� ��ȯ
//� ������ �޽����� ��� �ִ��� Ȯ���ϱ� ����
int Packet::GetMsgID()
{
	return mh.msgid;
}

//���� ���
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