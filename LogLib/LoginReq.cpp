#define aaareg

#include "LoginReq.h"
#include "../common/ehdef.h"
#pragma comment(lib,"..\\x64\\Debug\\PacketLib2.lib")
LoginReq::LoginReq(const char* id, const char* pw)
{
	strcpy_s(this->id, MAX_ID_LEN, id);
	strcpy_s(this->pw, MAX_PW_LEN, pw);

}
LoginReq::LoginReq(Packet2* ep)
{
	int idlen = 0;
	ep->Decapsulate(&idlen, sizeof(int));
	ep->Decapsulate(id, idlen);
	int pwlen = 0;
	ep->Decapsulate(&pwlen, sizeof(int));
	ep->Decapsulate(pw, pwlen);
}
void LoginReq::Send(HANDLE hFile)
{
	Packet2* ep = new Packet2(LOGIN_REQ);
	int idlen = strlen(id) + 1;
	ep->Capsulate(&idlen, sizeof(int));
	ep->Capsulate(id, idlen);
	int pwlen = strlen(pw) + 1;
	ep->Capsulate(&pwlen, sizeof(int));
	ep->Capsulate(pw, pwlen);
	ep->Serialize(hFile);
	delete ep;
}
const char* LoginReq::GetID()
{
	return id;
}
const char* LoginReq::GetPW()
{
	return pw;
}

//�α���