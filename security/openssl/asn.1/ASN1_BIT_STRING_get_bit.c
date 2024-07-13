/**
 * 本函数根据n 获取其比特位上的值
 */
#include <openssl/asn1.h>

int main(void)
{
	int ret,i,n;
	ASN1_BIT_STRING *a;

	a = ASN1_BIT_STRING_new();
	ASN1_BIT_STRING_set(a, "ab", 2);
	for (i = 0; i < 2 * 8; i++) {
		ret = ASN1_BIT_STRING_get_bit(a, i);
		printf("%d", ret);
	}
	ASN1_BIT_STRING_free(a);
	return 0;
}
//程序输出：0110000101100010
//说明：a 中”ab”的二进制既是0110000101100010。
