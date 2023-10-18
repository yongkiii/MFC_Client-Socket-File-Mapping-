#pragma once
#include "..\\PacketLib\Packet.h"
#include "..\\common\\ehdef.h"
#ifdef aaasel
#define SEL_DLL	__declspec(dllexport)
#else
#define SEL_DLL	__declspec(dllimport)
#endif

class SEL_DLL SelReq
{

	char id[MAX_ID_LEN];				//ȸ�� ���̵�
	int point;							//����Ʈ
	char pro_name[MAX_PRO_NAME_LEN];	//�����
	char ice_hot[MAX_ICE_HOT];			//hot_ice
	int pro_price;						//����
	int buy_num;						//���� ����
	int hap;							//��ǰ���� * ��ǰ ����
	char date[MAX_DATE_LEN];			//���� ��¥
	

public:
	SelReq( char* id, int point ,  char* pro_name,   char* ice_hot, int pro_price, int buy_num, int hap,   char* date);
	
	SelReq(Packet* pro_pac);
	
	 char* GetID();
	 char* GetProName();
	 char* GetIce_Hot();
	int GetProPrice();
	int GetPoint();
	int GetBuyNum();
	int GetHap();
	 char* GetDate();
	void Send(SOCKET sock);

};

