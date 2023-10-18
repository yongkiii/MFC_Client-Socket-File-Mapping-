#define aaareg
#include "RegRes.h"
#include "..\\common\\ehdef.h"

RegRes::RegRes(int result)
{
	this->result = result;
}
RegRes::RegRes(Packet2* ep)
{
	ep->Decapsulate(&result, sizeof(result));
}
void RegRes::Send(HANDLE hFile)
{
	Packet2* pac = new Packet2(REG_RES);
	pac->Capsulate(&result, sizeof(int));
	pac->Serialize(hFile);
	delete pac;
}
int RegRes::GetResult()
{
	return result;
}