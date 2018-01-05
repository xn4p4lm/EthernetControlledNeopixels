#include "stdafx.h"
#include "udptest.h"
#include <WS2tcpip.h>


using namespace std;

udptest::udptest()
{
	pkt_length = 60;
	WSAStartup(MAKEWORD(2, 2), &data);
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = inet_pton(AF_INET, "192.168.5.40", source);
	local.sin_port = htons(12); // choose any
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr("192.168.5.80");
	//inet_pton(AF_INET, "192.168.5.80", destination);
	dest.sin_port = htons(12);
	// create the socket
	s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	// bind to the local address
	bind(s, (sockaddr *)&local, sizeof(local));
}

void udptest::sendpkt(std::string dataString)
{
	//printf("test");
	*pkt = (char*)dataString.c_str();
	// send the pkt
	int ret = sendto(s, *pkt, pkt_length, 0, (sockaddr *)&dest, sizeof(dest));
}
