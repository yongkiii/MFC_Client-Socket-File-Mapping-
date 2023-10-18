#define aaareg

#include "RegReq.h"
#include "..\\common\ehdef.h"
#pragma comment(lib, "..\\x64\\Debug\\PacketLib2.lib")

RegReq::RegReq(const char* id, const char* pw, const char* name, const char* phone, const char* birth, const char* addr)
{
	strcpy_s(this->id, MAX_ID_LEN, id);
	strcpy_s(this->pw, MAX_PW_LEN, pw);
	strcpy_s(this->name, MAX_NAME_LEN, name);
	strcpy_s(this->phone, MAX_PHONE_LEN, phone);
	strcpy_s(this->birth, MAX_BIRTH_LEN, birth);
	strcpy_s(this->addr, MAX_ADDR_LEN, addr);
}

RegReq::RegReq(Packet2* pac)
{
	//id
	int idlen = 0;
	pac->Decapsulate(&idlen, sizeof(int));
	pac->Decapsulate(id, idlen);
	//pw
	int pwlen = 0;
	pac->Decapsulate(&pwlen, sizeof(int));
	pac->Decapsulate(pw, pwlen);
	//name
	int namelen = 0;
	pac->Decapsulate(&namelen, sizeof(int));
	pac->Decapsulate(name, namelen);
	//phone
	int phonelen = 0;
	pac->Decapsulate(&phonelen, sizeof(int));
	pac->Decapsulate(phone, phonelen);
	//birth
	int birthlen = 0;
	pac->Decapsulate(&birthlen, sizeof(int));
	pac->Decapsulate(birth, birthlen);
	//addr
	int addrlen = 0;
	pac->Decapsulate(&addrlen, sizeof(int));
	pac->Decapsulate(addr, addrlen);

}

void RegReq::Send(HANDLE hFile)
{
	Packet2* pac = new Packet2(REG_REQ);
	//id
	int idlen = strlen(id) + 1;
	pac->Capsulate(&idlen, sizeof(int));
	pac->Capsulate(id, idlen);
	//pw
	int pwlen = strlen(pw) + 1;
	pac->Capsulate(&pwlen, sizeof(int));
	pac->Capsulate(pw, pwlen);
	//name
	int namelen = strlen(name) + 1;
	pac->Capsulate(&namelen, sizeof(int));
	pac->Capsulate(name, namelen);
	//phone
	int phonelen = strlen(phone) + 1;
	pac->Capsulate(&phonelen, sizeof(int));
	pac->Capsulate(phone, phonelen);
	//birth
	int birthlen = strlen(birth) + 1;
	pac->Capsulate(&birthlen, sizeof(int));
	pac->Capsulate(birth, birthlen);
	//addr
	int addrlen = strlen(addr) + 1;
	pac->Capsulate(&addrlen, sizeof(int));
	pac->Capsulate(addr, addrlen);


	//
	pac->Serialize(hFile);
	delete pac;
}

const char* RegReq::GetID()
{
	return id;
}

const char* RegReq::GetPW()
{
	return pw;
}

const char* RegReq::GetName()
{
	return name;
}

const char* RegReq::GetPhone()
{
	return phone;
}

const char* RegReq::GetBirth()
{
	return birth;
}

const char* RegReq::GetAddr()
{
	return addr;
}

