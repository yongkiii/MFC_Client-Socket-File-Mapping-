#define aaareg

#include "LogoutReq.h"
#include "../common/ehdef.h"
#pragma comment(lib,"..\\x64\\Debug\\PacketLib2.lib")
LogoutReq::LogoutReq(const char* id, const char* pw)
{
	strcpy_s(this->id, MAX_ID_LEN, id);
	strcpy_s(this->pw, MAX_PW_LEN, pw);

}
LogoutReq::LogoutReq(Packet2* ep)
{
	int idlen = 0;
	ep->Decapsulate(&idlen, sizeof(int));
	ep->Decapsulate(id, idlen);
	int pwlen = 0;
	ep->Decapsulate(&pwlen, sizeof(int));
	ep->Decapsulate(pw, pwlen);
}
void LogoutReq::Send(HANDLE hFile)
{
	Packet2* ep = new Packet2(LOGOUT_REQ);
	int idlen = strlen(id) + 1;
	ep->Capsulate(&idlen, sizeof(int));
	ep->Capsulate(id, idlen);
	int pwlen = strlen(pw) + 1;
	ep->Capsulate(&pwlen, sizeof(int));
	ep->Capsulate(pw, pwlen);
	ep->Serialize(hFile);
	delete ep;
}
const char* LogoutReq::GetID()
{
	return id;
}
const char* LogoutReq::GetPW()
{
	return pw;
}
//·Î±×¾Æ¿ô