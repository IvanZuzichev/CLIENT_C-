#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "CClient.h"

#include <iostream>

#pragma comment(lib, "ws2_32.lib")

CClient::CClient()
{
	// ������ ���� ��������������� ��������� �������, ����� socket() ������ ������ 10093.
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0) //������������� ws2_32.dll ����� �������
	{
		std::cout << "������������� WSA �� �������" << std::endl;
		return;
	}

	m_sockClient = socket(AF_INET, SOCK_DGRAM, 0);

	m_TargetServer.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	m_TargetServer.sin_family = AF_INET;
	m_TargetServer.sin_port = htons(8090);

	if (m_sockClient == -1)
	{
		std::cout << "�������� ������ �� �������!" << std::endl;
		WSACleanup();
	}
	else
	{
		//��������� ���������� ��� ������������ ���������� � ��������
		sendto(m_sockClient, "������, ������", strlen("������, ������"), 0, (sockaddr*)&m_TargetServer, sizeof(m_TargetServer));
	}
}

void CClient::SendMsg(Calculator calc)
{
	sendto(m_sockClient, (char *)&calc, sizeof(calc), 0, (struct sockaddr*)&m_TargetServer, sizeof(m_TargetServer));
}
void CClient::RecMsg()
{
	char recBuf[1025];

	while (1)
	{
		int len = recvfrom(m_sockClient, recBuf, 1024, 0, 0, 0);
		if (len > 0)
		{
			recBuf[len] = '\0';
			std::cout << "������ �������: " << recBuf << std::endl;
		}
	}

}
CClient::~CClient()
{
	closesocket(m_sockClient);
	WSACleanup();
}