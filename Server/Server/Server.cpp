#include "pch.h"
#include <iostream>
#include <fstream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include <WinSock2.h>
#include <string>
#include <sstream>
#include <ctime>

#define ll long long

using namespace std;

SOCKET newConnection;

int main()
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		cout << "Error. Lib does not include" << endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int size_of_addr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	newConnection = accept(sListen, (SOCKADDR*)&addr, &size_of_addr);

	if (newConnection != 0)
	{
		cout << "Client connected!" << endl;
	}
	else
	{
		cout << "Error! Client couldn't connect" << endl;
	}

	while (1)
	{
		char _case[2];
		recv(newConnection, _case, sizeof(_case), NULL);

		if (_case[0] == '1')
		{
			char msg[256];
			recv(newConnection, msg, sizeof(msg), NULL);

			bool dbl = TRUE;

			string log, logpass = string(msg);
			istringstream iss(logpass);
			getline(iss, log, ' ');
			fstream f1;
			f1.open("logpass.txt", ios::in);
			if (f1)
			{
				while (getline(f1, logpass))
				{
					if (logpass.find(log) <= logpass.length() && logpass.find(log) >= 0) {
						char usr[2] = "0";
						send(newConnection, usr, sizeof(usr), NULL);
						Sleep(10);
						dbl = FALSE;
						f1.close();
					}
				}
			}
			if (dbl)
			{
				char usr[2] = "1";
				send(newConnection, usr, sizeof(usr), NULL);
				Sleep(10);
				ofstream f;
				f.open("logpass.txt", ios::app);
				f << msg << endl;
				f.close();
				f1.close();
			}
		}

		if (_case[0] == '2')
		{
			char msg[256];
			recv(newConnection, msg, sizeof(msg), NULL);

			string sN, log, logpass, login = string(msg);
			bool dbl = FALSE;
			fstream f1;
			f1.open("logpass.txt", ios::in);
			if (f1)
			{
				while (getline(f1, logpass))
				{
					if (logpass.find(login) <= logpass.length() && logpass.find(login) >= 0) {
						istringstream iss(logpass);
						getline(iss, log, ' ');
						getline(iss, sN);
						char usr[2] = "1";
						send(newConnection, usr, sizeof(usr), NULL);
						Sleep(10);
						dbl = TRUE;
						break;
					}
				}
				f1.close();
			}
			if (dbl)
			{
				srand(time(NULL));
				ll N = 0, V = 0, temp = 0;

				char _N[256];
				sprintf(_N, "%s", sN.c_str());
				send(newConnection, _N, sizeof(_N), NULL);
				Sleep(10);
				temp = 0;
				for (int i = 0; i < sizeof(_N); i++) {
					temp = _N[i] - '0';
					if (temp >= 0)
					{
						N += temp;
						N *= 10;
					}
				}
				N /= 10;
			
				char _V[256];
				recv(newConnection, _V, sizeof(_V), NULL);
				temp = 0;
				for (int i = 0; i < sizeof(_V); i++) {
					temp = _V[i] - '0';
					if (temp >= 0)
					{
						V += temp;
						V *= 10;
					}
				}
				V /= 10;

				for(int it = 0; it < 40; it++) 
				{
					ll y = 0, x = 0;

					char _x[256] = { 0 };
					recv(newConnection, _x, sizeof(_x), NULL);
					temp = 0;
					for (int i = 0; i < sizeof(_x); i++) {
						temp = _x[i] - '0';
						if (temp >= 0)
						{
							x += temp;
							x *= 10;
						}
					}
					x /= 10;

					int c = rand() % 2;
					char _c[2];
					_c[0] = c + '0';
					send(newConnection, _c, sizeof(_c), NULL);
					Sleep(10);

					char _y[256] = { 0 };
					recv(newConnection, _y, sizeof(_y), NULL);
					temp = 0;
					for (int i = 0; i < sizeof(_y); i++) {
						temp = _y[i] - '0';
						if (temp >= 0)
						{
							y += temp;
							y *= 10;
						}
					}
					y /= 10;
				
					ll A = 0, B = 0;

					if (c == 1)
					{
						A = (x * V) % N;
					}

					else
					{
						A = x % N;
					}

					B = (y * y) % N;
					
					if (A != B)
					{
						cout << "Cheater!" << endl;
						exit(1);
					}
				}
				cout << "Successful login for " << login << endl;
			}
			else
			{
				char usr[2] = "0";
				send(newConnection, usr, sizeof(usr), NULL);
				Sleep(10);
			}
		}
	}

	system("pause");
	return 0;
}