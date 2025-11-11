#include "mac.h"

int strtomacaddr(unsigned char *mac, char *str)
{
	char *p = str;
	unsigned char value = 0x0;
	int i = 0;

	while (*p != '\0') {
		if (*p == ':') {
			mac[i++] = value;
			value = 0x0;
		} else {
			unsigned char temp = *p;
			if (temp <= '9' && temp >= '0') {
				temp -= '0';
			} else if (temp <= 'f' && temp >= 'a') {
				temp -= 'a';
				temp += 10;
			} else if (temp <= 'F' && temp >= 'A') {
				temp -= 'A';
				temp += 10;
			} else {
				break;
			}
			value <<= 4;
			value |= temp;
		}
		p++;
	}
	mac[i] = value;
	return 0;
}

#ifdef TEST_MAIN
#include <stdio.h>

int main(void)
{
	int i;
	unsigned char mac[10];
	strtomacaddr(mac, "1c:69:7a:6e:f4:d0");

	for (i = 0; i < 6; i++)
		printf("%02x\n", mac[i]);
}
#endif

