#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "md5.h"


int main(void)
{
	int read_len;
	int i ;
	char temp[8]={0};
	unsigned char decrypt[16]={0};
	unsigned char decrypt32[64]={0};
	char hexbuf[128] = "12334567";

	MD5_CTX md5c;

	MD5Init(&md5c);
	read_len = strlen(hexbuf);
	MD5Update(&md5c,(unsigned char *)hexbuf,read_len);

	MD5Final(&md5c,decrypt);
	strcpy((char *)decrypt32, "");

	for (i = 0; i < 16; i++) {
		sprintf(temp,"%02x", decrypt[i]);
		strcat((char *)decrypt32, temp);
	}
	printf("md5: %s\n", decrypt32);

	return 0;
}
