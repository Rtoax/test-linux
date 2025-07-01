/**
 * 将ASCII 码转换为ASN1_STRING.
 * 转换后str->data 的前四个字节即变成"测试"。
 */
#include <openssl/asn1.h>

int main(void)
{
	BIO *bp;
	ASN1_STRING *str;
	char buf[50];
	int size,len;

	bp = BIO_new(BIO_s_mem());
	len = BIO_write(bp, "B2E2CAD4", 8);
	size = 50;
	(void)len;

	str = ASN1_STRING_new();
	a2i_ASN1_STRING(bp, str, buf, size);

	printf("buf = %s, str = %s\n", buf, str->data);

	BIO_free(bp);
	ASN1_STRING_free(str);
	return 0;
}
