#pragma once
#ifndef _CCLIENT_H
#define _CCLIENT_H

#include <winsock.h>
struct Calculator
{
	int one;
	int two;
};

class CClient
{
public:
	CClient();
	void RecMsg();
	void SendMsg(Calculator calc);
	~CClient();
private:
	SOCKET m_sockClient;
	sockaddr_in m_TargetServer;
};
#endif