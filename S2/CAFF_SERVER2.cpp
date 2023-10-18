//#include "stdafx.h"
#include "pch.h"
#include "..\\PacketLib\Packet.h"
#include "..\\common\ehdef.h"
#include "..\\SelLib\SelReq.h"
//#include "..\\SelLib\SelRes.h"
#include <afxdb.h>
#pragma comment(lib,"..\\x64\\Debug\\PacketLib")
#pragma comment(lib,"..\\x64\\Debug\\SelLIb")

void SelReqProc(Packet* p, SOCKET sock)
{
	int result;
	SelReq* sr = new SelReq(p);
	
	printf("추가 기기");
	//리스트들을 추가하는거 
	CDatabase db;
	bool re = db.OpenEx(TEXT("DSN=MFC; uid=scott;PWD=tiger"));

	if (re == FALSE)
	{
		//Handle the case where database connection fails.
		return;
	}
	result = SEL_REQ;
	if (result == SEL_REQ)
	{
		char buf[4000] = "";
		sprintf_s(buf,4000, "INSERT INTO SEL (S_ID, S_POINT, S_PRO_NAME, S_ICE_HOT, S_MONEY, S_NUM, S_HAP_MONEY, S_DATE) VALUES ('%s', %d, '%s', '%s', %d, %d, %d, '%s')",
		
			sr->GetID(), sr->GetPoint(), sr->GetProName(), sr->GetIce_Hot(), sr->GetProPrice(), sr->GetBuyNum(), sr->GetHap(), sr->GetDate());// sr->GetDate());
		wchar_t wbuf[4000];
		MultiByteToWideChar(CP_ACP, 0, buf, strlen(buf)+1, wbuf, 4000);
		//CString  query_str(buf);
		printf("추가완료");
		db.ExecuteSQL(wbuf);
		db.Close();
	}

}

DWORD DoIt(LPVOID param)
{
	SOCKET sock = (SOCKET)param;
	Packet* p = new Packet(sock);
	switch (p->GetMsgID())
	{
	case SEL_REQ: SelReqProc(p, sock); break;
	}
	closesocket(sock);
	return 0;
}