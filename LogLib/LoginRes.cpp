#define aaareg
#include "LoginRes.h"

#include "../common/ehdef.h"
LoginRes::LoginRes(int result)
{
	this->result = result;
}
LoginRes::LoginRes(Packet2* ep)
{
	ep->Decapsulate(&result, sizeof(result));
}
void LoginRes::Send(HANDLE hFile)
{
	Packet2* ep = new Packet2(LOGIN_RES);
	ep->Capsulate(&result, sizeof(int));
	ep->Serialize(hFile);
	delete ep;
}
int LoginRes::GetResult()
{
	return result;
}
//·Î±×ÀÎ °á°ú Ä¸½¶È­µğÄ¸½¶È­