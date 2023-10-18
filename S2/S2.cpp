// S2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "framework.h"
#include "S2.h"

#include "..\\PacketLib\Packet.h"
#include "..\\common\ehdef.h"
#include "..\\SelLib\SelReq.h"
#include "..\\SelLib\SelRes.h"
#include <stdio.h>
#include <conio.h>

#include "..\\SalesDB\SalesManager.h"
#pragma comment(lib,"../x64/Debug/SalesDB.lib")

#pragma warning(disable:4996)


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 유일한 애플리케이션 개체입니다.

CWinApp theApp;

using namespace std;
DWORD DoIt(LPVOID param);

DWORD PipeEntry(LPVOID param)
{
	//1. 소켓 생성
	SOCKET lissock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//2.네트워크 인터페이스와 결합
	SOCKADDR_IN servaddr = {};
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("192.168.0.58");
	servaddr.sin_port = htons(10202);
	if (bind(lissock, (SOCKADDR*)&servaddr, sizeof(servaddr)) == -1)
	{
		printf("네트워크 인터페이스와 결합 오류\n");
		return 0;
	}
	//3.백로그 큐 크기 결정
	listen(lissock, 5);

	//4.AcceptLoop
	SOCKET dosock;
	SOCKADDR_IN cliaddr = {};
	int len = sizeof(cliaddr);
	while (1)
	{
		dosock = accept(lissock, (SOCKADDR*)&cliaddr, &len);
		if (dosock == -1)
		{
			break;
		}
		CloseHandle(CreateThread(0, 0, DoIt, (LPVOID)dosock, 0, 0));
	}
	//5.소켓 닫기
	closesocket(dosock);
	
	return 0;
}
//char SelectMenu()
//{
//	system("cls");
//	printf("시작");
//	return _getch();
//}

int main()
{
	

	WSAData wd;
	WSAStartup(MAKEWORD(2, 2), &wd);



	printf("구매 데이터 서버 시작!");
	DWORD tid;
	CloseHandle(CreateThread(0, 0, PipeEntry, 0, 0, &tid));
	//DoIt(&wd); 
	_getch();
	//printf("끝");
	WSACleanup();
	

    return 0;
}
