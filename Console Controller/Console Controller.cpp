// Console Controller.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "udptest.h"


int main()
{
	udptest udp;
	std::string s = "null";
	while(s.compare("exit"))
	{
		std::cin >> s;
		udp.sendpkt(s);
	}
    return 0;
}

