//ASN1_ENUMERATED_get
//获取ASN1_ENUMERATED 的值；示例如下：

#include <openssl/asn1.h>

int main(void)
{
	long ret;
	ASN1_ENUMERATED *a;
	a=ASN1_ENUMERATED_new();
	ASN1_ENUMERATED_set(a,(long)155);
	ret=ASN1_ENUMERATED_get(a);
	printf("%ld\n",ret);
	return 0;
}
