#define aaasel
#include "SelRes.h"
#include "../common/ehdef.h"


SelRes::SelRes(int result)
{
	this->result = result;
}
SelRes::SelRes(Packet* ep)
{
	ep->Decapsulate(&result, sizeof(result));
}

int SelRes::GetResult()
{
	return result;
}

void SelRes::Send(SOCKET sock)
{
	Packet* ep = new Packet(SEL_RES);
	ep->Capsulate(&result, sizeof(int));
	ep->Send(sock);
	delete ep;
}