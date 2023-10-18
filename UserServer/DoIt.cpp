#include "..\\PacketLib2\\Packet2.h"
#include "..\\RegLib\\RegReq.h"
#include "..\\RegLib\\UnRegReq.h"
#include "..\\RegLib\\RegRes.h"
#include "..\\LogLib\\LoginReq.h"
#include "..\\LogLib\\LogoutReq.h"
#include "..\\LogLib\\LoginRes.h"

#include "..\\UserDataLib\\UserData.h"
#include "..\\common\\ehdef.h"


void RegReqProc(Packet2* ep,HANDLE hPipe)
{
	RegReq* rr = new RegReq(ep);
	UserData *ud = FindUserData(rr->GetID());
	int result = REG_RES_NO;
	if (ud)
	{
		printf("(%s) �̹� ���� ������ ID�Դϴ�.\n", rr->GetID());
	}
	else
	{
		AddUserData(rr->GetID(), rr->GetPW(), rr->GetName(),rr->GetPhone(),rr->GetBirth(),rr->GetAddr());
		result = REG_RES_OK;
		printf("%s %s %s %s %s %s ���� ����\n", rr->GetID(), rr->GetPW(), rr->GetName(), rr->GetPhone(), rr->GetBirth(), rr->GetAddr());
	}
	RegRes* rres = new RegRes(result);
	rres->Send(hPipe);
	FlushFileBuffers(hPipe);//�������� �ݱ� ���� ������ ���� ��Ŷ�� �����ϰ� ���� �� �ְ� 
	delete rres;
}
void UnRegReqProc(Packet2* ep, HANDLE hPipe)
{
	UnRegReq* urr = new UnRegReq(ep);
	UserData* ud = FindUserData(urr->GetID());
	if (ud == 0)
	{
		printf("ũ��Ŀ(black ��Ŀ)�� ���Գ���\n");
		return;
	}
	if (strcmp(ud->pw, urr->GetPW()) == 0)
	{
		RemoveUserData(urr->GetID());
		printf("%s Ż���Ͽ����ϴ�.\n", urr->GetID());
	}
	else
	{
		printf("�Ƹ��� ũ��Ŀ(black ��Ŀ)�� ���Գ���... ��й�ȣ�� �𸧽÷�...\n");
		return;
	}
}
void LoginReqProc(Packet2* ep, HANDLE hPipe)
{
	LoginReq* lr = new LoginReq(ep);
	UserData* ud = FindUserData(lr->GetID());
	int result = LOGIN_RES_FA;
	if (ud==0)
	{
		result = LOGIN_RES_NOI;
		printf("(%s) ���̵� ���µ� �α� ��û�߳׿�.\n", lr->GetID());
	}
	else
	{
		if (strcmp(lr->GetPW(), ud->pw) == 0)
		{
			if (ud->status == LOGINED)
			{
				result = LOGIN_RES_ALR;
			}
			else
			{
				ud->status = LOGINED;
				result = LOGIN_RES_OK;
				printf("%s %s �α� ����\n", lr->GetID(), lr->GetPW());
			}
		}
		else
		{
			result = LOGIN_RES_NOC;
			printf("(%s) ��й�ȣ�� �ٸ��� �α� ��û�߳׿�.\n", lr->GetID());
		}				
		
	}
	LoginRes* lres = new LoginRes(result);
	lres->Send(hPipe);
	FlushFileBuffers(hPipe);//�������� �ݱ� ���� ������ ���� ��Ŷ�� �����ϰ� ���� �� �ְ� 
	delete lres;
}
void LogoutReqProc(Packet2* ep, HANDLE hPipe)
{
	LogoutReq* lor = new LogoutReq(ep);
	UserData* ud = FindUserData(lor->GetID());
	if (ud == 0)
	{
		printf("ũ��Ŀ(black ��Ŀ)�� ���Գ���(%s ����)\n",lor->GetID());
		return;
	}
	if (strcmp(ud->pw, lor->GetPW()) == 0)
	{
		if (ud->status != LOGINED)
		{
			printf("ũ��Ŀ(black ��Ŀ)�� ���Գ���(%s �α� ���°� �ƴѵ� �α� �ƿ� ��û)\n", lor->GetID());
		}
		else
		{
			ud->status = REGED;
			printf("%s �α� �ƿ� �Ͽ����ϴ�.\n", lor->GetID());
		}
	}
	else
	{
		printf("%s �Ƹ��� ũ��Ŀ(black ��Ŀ)�� ���Գ���... ��й�ȣ�� �𸧽÷�...\n",lor->GetID());
		return;
	}
}
DWORD DoIt(LPVOID param)
{
	HANDLE hPipe = (HANDLE)param;
	Packet2* ep = new Packet2(hPipe);
	switch (ep->GetMsgID())
	{
	case REG_REQ: RegReqProc(ep, hPipe); break;
	case UNREG_REQ: UnRegReqProc(ep, hPipe); break;
	case LOGIN_REQ: LoginReqProc(ep, hPipe); break;
	case LOGOUT_REQ: LogoutReqProc(ep, hPipe); break;
	}
	CloseHandle(hPipe);
	return 0;
}