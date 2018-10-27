// Win32Project1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	char* a = new char[6];
	a[0] = 'h';
	a[1] = 'e';
	a[2] = 'l';
	a[3] = 'l';
	a[4] = 'o';
	a[5] = '\0';

	cout << a << '\n';

	char* end, *begin;
	end = &a[strlen(a) - 1];
	begin = &a[0];

	for (unsigned int i = 0; i < strlen(a)/2; i++)
	{
		*begin ^= *end;
		*end ^= *begin;
		*begin ^= *end;

		begin++;
		end--;
	}

	cout << a << '\n';

	system("pause");
	return 0;
}

