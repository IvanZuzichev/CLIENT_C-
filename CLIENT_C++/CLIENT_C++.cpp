#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include<Windows.h>
#include "CClient.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	CClient client_UDP;

	thread RecProc(&CClient::RecMsg, &client_UDP);

	while (1)
	{
		SetConsoleCP(1251);
		setlocale(0, "");
		int x;
		int y;
		cout << "Введите первое число";
		cin >> x;
		cout << "Введите второе число";
		cin >> y;
		Calculator calc;
		calc.one = x;
		calc.two = y;

		client_UDP.SendMsg(calc);
	}


	RecProc.join();
	cout << "Пример!" << endl;
	system("pause");
	return 0;
}
