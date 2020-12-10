// ZEI-stlib.cpp : Определяет функции для статической библиотеки.
//

#include "pch.h"
#include "framework.h"
#include <iostream>

extern "C" {
	int symblen(char* symb) {
		int slen = 0;
		while(symb[slen] != '\0')
			slen++;
		return slen;
	}
	//Может тут границы tiny
	int symbtotiny(char* symb) {
		int number = 0; // число
		int i = 0;
		int sign = 0; // знак числа 0- положительное, 1 — отрицательное
		if (symb[i] == '-') 	{
			sign = 1;
			i++;
		}
		while (symb[i] >= 0x30 && symb[i] <= 0x39) {
			number = number + (symb[i] & 0x0F);
			number = number * 10;
			i++;
		}
		number = number / 10;
		if (sign == 1)
			number = -number;
		return number;
	}
	//мб инт
	void show(int tiny)	{
		std::cout << tiny << std::endl;
	}
	void showstr(char* symb)	{
		if (symb == nullptr)	{
			std::cout << std::endl;
		}
		for (int i = 0; symb[i] != '\0'; i++)
			std::cout << symb[i] << std::endl;
	}
}