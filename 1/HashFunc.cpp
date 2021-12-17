﻿#include "HashFunc.h"
#include <iostream>
#include <fstream>
#include <cstring>

uint32_t hashpunk::adler32(std::istream &file)
{
	uint32_t a = 1, b = 0;
	unsigned char s;
	while (file.read((char*)&s, sizeof(unsigned char)))
	{
		std::streamsize bytes = file.gcount();
		if (!bytes) break;
		a = (a + s) % 65521;
		b = (b + a) % 65521;
	}
	return ((b << 16) | a);
}

uint64_t hashpunk::sum64(std::istream &file)
{
	uint64_t sum = 0, k = 0;
	int g = 0;
	unsigned char s;
	while (file.read((char*)&s, sizeof(unsigned char)))
	{
		std::streamsize bytes = file.gcount();
		if (!bytes) break;
		if (g == 7)
		{
			sum += k;
			k = 0;
		}
		k = (k << 8) | s;
		g = (g + 1) % 8;
	}
	if (g != 0)
	{
		sum += k;
	}
	return sum;
}