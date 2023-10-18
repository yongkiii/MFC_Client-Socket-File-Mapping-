#define aaareg
#include "UnRegReq.h"
#include "..\\common\ehdef.h"
#pragma comment(lib,"..\\x64\\Debug\\PacketLib2.lib")


UnRegReq::UnRegReq(const char* id, const char* pw)
{
	strcpy_s(this->id, MAX_ID_LEN, id);
	strcpy_s(this->pw, MAX_PW_LEN, pw);
}
UnRegReq::UnRegReq(Packet2* pac)
{
	int idlen = 0;
	pac->Decapsulate(&idlen, sizeof(int));
	pac->Decapsulate(id, idlen);
	int pwlen = 0;
	pac->Decapsulate(&pwlen, sizeof(int));
	pac->Decapsulate(pw, pwlen);
}
void UnRegReq::Send(HANDLE hFile)
{
	Packet2* pac = new Packet2(UNREG_REQ);
	int idlen = strlen(id) + 1;
	pac->Capsulate(&idlen, sizeof(int));
	pac->Capsulate(id, idlen);
	int pwlen = strlen(pw) + 1;
	pac->Capsulate(&pwlen, sizeof(int));
	pac->Capsulate(pw, pwlen);
	pac->Serialize(hFile);
	delete pac;
}
const char* UnRegReq::GetID()
{
	return id;
}
const char* UnRegReq::GetPW()
{
	return pw;
}
//È¸¿øÅ»Åð