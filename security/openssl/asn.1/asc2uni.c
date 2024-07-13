/**
 * 将ASCII 码转换为UNICODE
 */
#include <stdio.h>
#include <string.h>
#include <openssl/crypto.h>

int main(void)
{
	char asc[50]={"B2E2CAD4"};
	char uni[50], *p, *q;
	int ascLen, unlen;

	ascLen = strlen(asc);
	//对‘asc2uni’未定义的引用?????????
	q = asc2uni(asc,ascLen,NULL,&unlen);

	OPENSSL_free(q);
	return 0;
}

