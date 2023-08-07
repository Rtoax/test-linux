#include "memshow.h"

int main()
{
	char str[] = {
		"1234567890abcdefghijklmnopqrstuvwxyz:;,."
	};

	memshow(">>  ", str, sizeof(str));
	memshow(">>>>", str, sizeof(str));
}
