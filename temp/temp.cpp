// temp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <winsock2.h>
#include <Windows.h>
#include <iostream>

using namespace std;
#pragma comment(lib, "ws2_32.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	SOCKET Socket;
	SOCKADDR_IN SockAddr;
	struct hostent *host;
	string url = "www.baidu.com";

	// ע��dll
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		cout << "WSAStartup failed.\n";
		system("pause");
	}
	cout << "WSADATA.wHighVersion: \t" << wsaData.wHighVersion << "\r\n";
	cout << "WSADATA.wVersion: \t" << wsaData.wVersion << "\r\n";

	// �����׽���
	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// ��ȡ������ַ
	host = gethostbyname(url.c_str());

	// �����׽��ֵ�ַ
	SockAddr.sin_port = htons(80);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.S_un.S_addr = *((unsigned long*)host->h_addr_list)

	WSACleanup();

	system("pause");
	return 0;
}

