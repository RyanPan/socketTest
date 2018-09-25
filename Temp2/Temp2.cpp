// Temp2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <winsock2.h>
#include <Windows.h>
#include <string>
#include <iostream>

using namespace std;
#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	char *ptr, **pptr;
	struct hostent *hptr;
	char str[32];
	DWORD dwError;
	struct in_addr addr;
	//IN_ADDR addr2; // Same as above
	int i = 0;

	//cout << "arg count: " << argc << endl;
	//cout << "arg[0]: " << argv[0] << endl;
	//cout << "arg[1]: " << argv[1] << endl;
	//cout << "arg[2]: " << argv[2] << endl;

	ptr = argv[1];

	// 注册dll
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		cout << "WSAStartup failed.\n";
		system("pause");
	}

	// 获取主机名
	hptr = gethostbyname(ptr);
	if (hptr == NULL)
	{
        dwError = WSAGetLastError();
        if (dwError != 0) {
			cout << "gethostbyname error for host: " << ptr << endl;
            if (dwError == WSAHOST_NOT_FOUND) {
                printf("Host not found\n");
                return 1;
            } else if (dwError == WSANO_DATA) {
                printf("No data record found\n");
                return 1;
            } else {
                printf("Function failed with error: %ld\n", dwError);
                return 1;
            }
        }
		return 0;
	}
	addr.s_addr = inet_addr(ptr);

	// 打印主机名
	cout << "Offical host name: " << hptr->h_name << endl;

	// 打印所有主机别名
	for (pptr = hptr->h_aliases; *pptr != NULL; pptr++)
	{
		cout << "alias: " << *pptr << endl;
	}

	// 打印 IP 地址
	switch (hptr->h_addrtype)
	{
		case AF_INET:
		case AF_INET6:
			pptr = hptr->h_addr_list;
			for (; *pptr != NULL; pptr++)
			{
				cout << "address: "	<< pptr << endl;

				//printf("first address: %s\n", inet_ntop(hptr->h_addrtype, hptr->h_addr, str, sizeof(str)));

				cout << "IP: ";
				cout << (short)((unsigned char*)*pptr)[0] << ".";
				cout << (short)((unsigned char*)*pptr)[1] << ".";
				cout << (short)((unsigned char*)*pptr)[2] << ".";
				cout << (short)((unsigned char*)*pptr)[3] << endl;
				addr.s_addr = *(u_long *) hptr->h_addr_list[i++];
				cout << "IP: " << inet_ntoa(addr) << endl;
			}
		break;
		default:
			cout << "unknow address type" << endl;
	}

	WSACleanup();

	return 0;
}

