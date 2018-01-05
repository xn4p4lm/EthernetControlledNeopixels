#pragma once

#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <WS2tcpip.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

class udptest
{

private:
	SOCKET s;
	char source[1024];
	char destination[1024];
	string myAddr;
	char *pkt[60];
	size_t pkt_length;
	sockaddr_in dest;
	sockaddr_in local;
	WSAData data;

public:
	udptest();
	void sendpkt(string dataString);
};
