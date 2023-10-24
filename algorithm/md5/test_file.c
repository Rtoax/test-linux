#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "md5.h"


#define FORWORD_FW "/etc/os-release"

int calc_md5(char *filename, char *dest)
{
	int i;
	int filelen = 0;
	int read_len;
	char temp[8]={0};
	char hexbuf[128]={0};
	unsigned char decrypt[16]={0};
	unsigned char decrypt32[64]={0};
	MD5_CTX md5;

	int fdf;

	fdf = open(filename, O_RDONLY);
	if (fdf < 0) {
		printf("%s not exist\n", filename);
		return -1;
	}

	MD5Init(&md5);
	while (1) {
		read_len = read(fdf, hexbuf, sizeof(hexbuf));
		if (read_len < 0) {
			close(fdf);
			return -1;
		}
		if (read_len == 0)
			break;

		filelen += read_len;
		MD5Update(&md5, (unsigned char *)hexbuf, read_len);
	}

	MD5Final(&md5, decrypt);
	strcpy((char *)decrypt32, "");

	for (i = 0; i < 16; i++) {
		sprintf(temp,"%02x", decrypt[i]);
		strcat((char *)decrypt32, temp);
	}
	strcpy(dest, (char *)decrypt32);

	printf("md5: %s len=%d\n", dest, filelen);
	close(fdf);

	return filelen;
}

int main(int argc, char *argv[])
{
	int filelen;
	char md5_str[64]={0};

	filelen = calc_md5(FORWORD_FW, md5_str);
	if (filelen < 0) {
		printf("calc_md5 fail\n");
		return -1;
	}
	return 0;
}
