#include "..\\PacketLib2\\Packet2.h"
#include "..\\RegLib\\RegReq.h"
#include "..\\RegLib\\RegRes.h"
#include "..\\LogLib\LoginReq.h"
#include "..\\UserDataLib\\UserData.h"
#include "..\\common\\ehdef.h"
#include <conio.h>
#pragma comment(lib,"..\\x64\\Debug\\PacketLib2.lib")
#pragma comment(lib,"..\\x64\\Debug\\RegLib.lib")
#pragma comment(lib,"..\\x64\\Debug\\LogLib.lib")
#pragma comment(lib,"..\\x64\\Debug\\UserDataLib.lib")
DWORD DoIt(LPVOID param);

void Init()
{
	MakeDB();
	Loading();
}
DWORD PipeEntry(LPVOID param)
{
	HANDLE hPipe;
	bool check;
	while (1)
	{
		hPipe = CreateNamedPipe(REG_PNAME, PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE, 5,
			4096, 4096, 0, 0);
		check = ConnectNamedPipe(hPipe, 0);
		if ((check == false) && (GetLastError() == ERROR_PIPE_CONNECTED))
		{
			check = true;
		}
		if (check)
		{
			DWORD tid;
			CloseHandle(CreateThread(0, 0, DoIt, hPipe, 0, &tid));
		}
		else
		{
			break;
		}
	}
	return 0;
}
void Run()
{
	DWORD tid;
	CloseHandle(CreateThread(0, 0, PipeEntry, 0, 0, &tid));
	printf("로그인/ 회원가입 서버 : 아무키나 누르면 서버를 종료합니다.");
	_getche();
}
void Exit()
{
	CleanUserDB();
}
int main()
{
	Init();
	Run();
	Exit();
	return 0;
}