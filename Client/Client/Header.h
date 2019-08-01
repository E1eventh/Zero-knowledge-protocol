#pragma once
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#include <WinSock2.h>
#include <string>
#include <ctime>

#define ll long long

using namespace std;

bool isSimple(ll n) {
	for (ll i = 2; i <= sqrt(n); i++) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

ll powmod(ll num, ll deg, ll mod)
{
	ll res = 1;
	while (deg)
	{
		if (deg & 1) {
			res = ((num % mod) * (res % mod)) % mod;
		}
		num = ((num % mod) * (num % mod)) % mod;
		deg >>= 1;
	}
	return res;
}

ll gcd(ll a, ll b) {
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}

int reg(string log, ll &N)
{
	ll P = 0, Q = 0, V = 0, s = 0;

	srand(time(NULL));

	P = rand() % 100000 + 1000;
	while (!isSimple(P))
	{
		P = rand() % 10000 + 1000;
	}

	Q = rand() % 100000 + 1000;
	while (!isSimple(Q))
	{
		Q = rand() % 100000 + 1000;
	}

	N = P * Q;
	
	s = rand() % (N - 1) + 485;
	while (gcd(s, N) != 1)
	{
		s = rand() % (N - 1) + 1;
	}

	//V = powmod(s, 2, N);

	return s;
}