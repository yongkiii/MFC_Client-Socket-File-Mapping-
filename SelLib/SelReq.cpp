#define aaasel

#include "SelReq.h"
#include "..\\common\ehdef.h"
#pragma comment(lib,"..\\x64\\Debug\\PacketLib.lib")
//#pragma comment(lib,"ws2_32")

SelReq::SelReq(  char* id, int point,  char* pro_name,  char* ice_hot, int pro_price, int buy_num, int hap,  char* date)
{
	strcpy_s(this->id, MAX_ID_LEN, id);
	this->point = point;
	strcpy_s(this->pro_name, MAX_PRO_NAME_LEN, pro_name);
	strcpy_s(this->ice_hot, MAX_ICE_HOT, ice_hot);
	this->pro_price = pro_price;
	this->buy_num = buy_num;
	this->hap = hap;
	strcpy_s(this->date, MAX_DATE_LEN, date);
}
SelReq::SelReq(Packet* pro_pac)
{
	//id
	int idlen = 0;
	pro_pac->Decapsulate(&idlen, sizeof(int));
	pro_pac->Decapsulate(id, idlen);

	//point 
	pro_pac->Decapsulate(&point, sizeof(int));
	//pro_name
	int pro_name_len = 0;
	pro_pac->Decapsulate(&pro_name_len, sizeof(int));
	pro_pac->Decapsulate(pro_name, pro_name_len);

	//ice_hot
	int ice_hot_len = 0;
	pro_pac->Decapsulate(&ice_hot_len, sizeof(int));
	pro_pac->Decapsulate(ice_hot, ice_hot_len);

	//pro_price
	pro_pac->Decapsulate(&pro_price, sizeof(int));
	//buy_num
	pro_pac->Decapsulate(&buy_num, sizeof(int));
	//hap
	pro_pac->Decapsulate(&hap, sizeof(int));
	//date
	int date_len = 0;
	pro_pac->Decapsulate(&date_len, sizeof(int));
	pro_pac->Decapsulate(date, date_len);
}
 char* SelReq::GetID()
{
	return id;
}
 char* SelReq::GetProName()
{
	return pro_name;
}
 char* SelReq::GetIce_Hot()
{
	return ice_hot;
}
int SelReq::GetPoint()
{
	return point;
}
int SelReq::GetProPrice()
{
	return pro_price;
}
int SelReq::GetBuyNum()
{
	return buy_num;
}
int SelReq::GetHap()
{
	return hap;
}
 char* SelReq::GetDate()
{
	return date;
}
void SelReq::Send(SOCKET sock)
{
	Packet* pro_pac = new Packet(SEL_REQ);

	//id
	int idlen = strlen(id) + 1;
	pro_pac->Capsulate(&idlen, sizeof(int));
	pro_pac->Capsulate(id, idlen);
	//point 
	pro_pac->Capsulate(&point, sizeof(int));

	//pro_name
	int pro_name_len = strlen(pro_name) + 1;
	pro_pac->Capsulate(&pro_name_len, sizeof(int));
	pro_pac->Capsulate(pro_name, pro_name_len);

	//ice_hot
	int ice_hot_len = strlen(ice_hot) + 1;
	pro_pac->Capsulate(&ice_hot_len, sizeof(int));
	pro_pac->Capsulate(ice_hot, ice_hot_len);


	//pro_price
	pro_pac->Capsulate(&pro_price, sizeof(int));

	//buy_num
	pro_pac->Capsulate(&buy_num, sizeof(int));

	//hap
	pro_pac->Capsulate(&hap, sizeof(int));
	//date
	int datelen = strlen(date) + 1;
	pro_pac->Capsulate(&datelen, sizeof(int));
	pro_pac->Capsulate(date, datelen);

	pro_pac->Send(sock);
	delete pro_pac;
}