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
		printf("(%s) 이미 가입 상태의 ID입니다.\n", rr->GetID());
	}
	else
	{
		AddUserData(rr->GetID(), rr->GetPW(), rr->GetName(),rr->GetPhone(),rr->GetBirth(),rr->GetAddr());
		result = REG_RES_OK;
		printf("%s %s %s %s %s %s 가입 성공\n", rr->GetID(), rr->GetPW(), rr->GetName(), rr->GetPhone(), rr->GetBirth(), rr->GetAddr());
	}
	RegRes* rres = new RegRes(result);
	rres->Send(hPipe);
	FlushFileBuffers(hPipe);//파이프를 닫기 전에 마지막 보낸 패킷이 안전하게 보낼 수 있게 
	delete rres;
}
void UnRegReqProc(Packet2* ep, HANDLE hPipe)
{
	UnRegReq* urr = new UnRegReq(ep);
	UserData* ud = FindUserData(urr->GetID());
	if (ud == 0)
	{
		printf("크래커(black 해커)가 들어왔나벼\n");
		return;
	}
	if (strcmp(ud->pw, urr->GetPW()) == 0)
	{
		RemoveUserData(urr->GetID());
		printf("%s 탈퇴하였습니다.\n", urr->GetID());
	}
	else
	{
		printf("아마도 크래커(black 해커)가 들어왔나벼... 비밀번호도 모름시롱...\n");
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
		printf("(%s) 아이디가 없는데 로긴 요청했네요.\n", lr->GetID());
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
				printf("%s %s 로긴 성공\n", lr->GetID(), lr->GetPW());
			}
		}
		else
		{
			result = LOGIN_RES_NOC;
			printf("(%s) 비밀번호를 다르게 로긴 요청했네요.\n", lr->GetID());
		}				
		
	}
	LoginRes* lres = new LoginRes(result);
	lres->Send(hPipe);
	FlushFileBuffers(hPipe);//파이프를 닫기 전에 마지막 보낸 패킷이 안전하게 보낼 수 있게 
	delete lres;
}
void LogoutReqProc(Packet2* ep, HANDLE hPipe)
{
	LogoutReq* lor = new LogoutReq(ep);
	UserData* ud = FindUserData(lor->GetID());
	if (ud == 0)
	{
		printf("크래커(black 해커)가 들어왔나벼(%s 없음)\n",lor->GetID());
		return;
	}
	if (strcmp(ud->pw, lor->GetPW()) == 0)
	{
		if (ud->status != LOGINED)
		{
			printf("크래커(black 해커)가 들어왔나벼(%s 로긴 상태가 아닌데 로그 아웃 요청)\n", lor->GetID());
		}
		else
		{
			ud->status = REGED;
			printf("%s 로그 아웃 하였습니다.\n", lor->GetID());
		}
	}
	else
	{
		printf("%s 아마도 크래커(black 해커)가 들어왔나벼... 비밀번호도 모름시롱...\n",lor->GetID());
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