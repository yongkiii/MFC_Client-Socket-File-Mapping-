#define packetpipe123123
#include "Packet2.h"

// �޽��� ���̵�(msgid)�� �Է¹޾� ��ü�� �ʱ�ȭ
Packet2::Packet2(int msgid)
{
	mh2.msgid = msgid;
	mh2.bdlen = 0;
}

Packet2::Packet2(HANDLE hFile)
{
	DWORD dw;
	ReadFile(hFile, &mh2, sizeof(MsgHead2), &dw, 0);
	ReadFile(hFile, body, mh2.bdlen, &dw, 0);
	offset = body;
}

//�����͸� ��Ŷ �ٵ� ĸ��ȭ(�߰�)
//�Էµ� ������(data)�� ����(dlen)�� ��Ŷ �ٵ�(body)�� �߰��ϰ�, �ٵ� ���̸� ������Ʈ
void Packet2::Capsulate(void* data, int dlen)
{
	memcpy_s(body + mh2.bdlen, MAX_BODY_LEN - mh2.bdlen, data, dlen);
	mh2.bdlen += dlen;
}

// �����͸� ��ĸ��ȭ(����)
void Packet2::Decapsulate(void* base, int blen)
{
	if ((offset + blen - body) > mh2.bdlen)
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
void Packet2::Serialize(HANDLE hFile)
{
	DWORD dw;
	WriteFile(hFile, &mh2, sizeof(MsgHead2), &dw, 0);
	WriteFile(hFile, body, mh2.bdlen, &dw, 0);
}

//��Ŷ�� �޽��� ���̵�(msgid)�� ��ȯ
//� ������ �޽����� ��� �ִ��� Ȯ���ϱ� ����
int Packet2::GetMsgID()
{
	return mh2.msgid;
}
