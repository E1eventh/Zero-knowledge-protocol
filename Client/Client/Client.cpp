#include "pch.h"
#include "Header.h"

int main()
{
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		cout << "Error. Lib does not include" << endl;
	}

	SOCKADDR_IN addr;
	int size_of_addr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
	{
		cout << "Error: failed connect to server" << endl;
		return 1;
	}
	
	while (1)
	{
		int check = 0;

		system("cls");
		cout << "1. Rigistration" << endl;
		cout << "2. Log in" << endl;
		cout << "3. Exit" << endl << endl;

		cin >> check;

		if (check == 1)
		{
			char _case[2] = "1";
			send(Connection, _case, sizeof(_case), NULL);
			Sleep(10);

			system("cls");
			string log;
			cout << "Enter your login please" << endl;
			cin >> log;

			ll s = 0, N = 0;
			s = reg(log, N);

			char msg[256];
			sprintf(msg, "%s %ld", log.c_str(), N);
			send(Connection, msg, sizeof(msg), NULL);
			Sleep(10);

			char usr[2];
			recv(Connection, usr, sizeof(usr), NULL);
			if (usr[0] == '1')
			{
				cout << "Your password is: " << s << endl;
				system("pause");
			}

			else 
			{
				cout << "User with this name is already registered" << endl;
				system("pause");
				continue;
			}
		}
		if (check == 2)
		{
			char _case[2] = "2";
			send(Connection, _case, sizeof(_case), NULL);
			Sleep(10);

			system("cls");
			string log, pass;
			cout << "Enter your login" << endl;
			cin >> log;

			char logpass[256], usr[2];
			sprintf(logpass, "%s", log.c_str());
			send(Connection, logpass, sizeof(logpass), NULL);
			Sleep(10);

			recv(Connection, usr, sizeof(usr), NULL);

			if (usr[0] == '1')
			{
				ll  s = 0, V = 0, N = 0, temp = 0;

				char _N[256];
				recv(Connection, _N, sizeof(_N), NULL);
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
			
				cout << "Enter your password" << endl;
				cin >> s;

				V = powmod(s, 2, N);
				char _V[256];
				sprintf(_V, "%ld", V);
				send(Connection, _V, sizeof(_V), NULL);
				Sleep(10);

				for (int it = 0; it < 40; it++)
				{
					ll x = 0, r = 0, y = 0;

					r = rand() % (N - 1) + 1;
					x = powmod(r, 2, N);
					char _x[256] = { 0 };
					sprintf(_x, "%ld", x);
					send(Connection, _x, sizeof(_x), NULL);
					Sleep(10);

					char _c[2];
					recv(Connection, _c, sizeof(_c), NULL);
					if (_c[0] == '1')
					{
						y = (r * s) % N;
					}
					else
					{
						y = r % N;
					}

					char _y[256] = { 0 };
					sprintf(_y, "%ld", y);
					send(Connection, _y, sizeof(_y), NULL);
					Sleep(10);
				}
			}

			else
			{
				cout << "You don't registrate here" << endl;
				system("pause");
				continue;
			}
			system("pause");
		}
		if (check == 3)
		{
			char _case[2] = "0";
			send(Connection, _case, sizeof(_case), NULL);
			Sleep(10);
			return 0;
		}
	}

	system("pause");
	return 0;
}