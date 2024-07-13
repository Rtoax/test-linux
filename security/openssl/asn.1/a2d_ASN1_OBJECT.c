/**
 * 计算 OID 的DER 编码，比如将2.99999.3 形式转换为内存形式。示例：
 * 输出结果：buf 内存值为：86 8D 6F 03
 */
#include <openssl/asn1.h>

int main(void)
{
	const char oid[]={"2.99999.3.12.12..12.1.23.12.31.23."};
	int i;
	unsigned char *buf;


	i = a2d_ASN1_OBJECT(NULL, 0, oid, -1);
	if (i <= 0)
		return -1;

	printf("i = %d\n", i);

	buf = (unsigned char *)malloc(sizeof(char) * i);
	i = a2d_ASN1_OBJECT(buf, i, oid, -1);

	printf("buf = %s\n", buf);

	free(buf);
	return 0;
}
