// int ASN1_STRING_cmp(ASN1_STRING *a, ASN1_STRING *b);
// ASN1_STRING 比较。ossl_typ.h 中绝大多数ASN1 基本类型都定义为
// ASN1_STRING，所以，此函数比较通用。示例如下：
// # ./a.out
// -3
// 0
#include <openssl/asn1.h>

int main(void)
{
	int ret;
	ASN1_STRING *a,*b,*c;
	a=ASN1_STRING_new();
	b=ASN1_STRING_new();
	ASN1_STRING_set(a,"abc",3);
	ASN1_STRING_set(b,"def",3);
	ret=ASN1_STRING_cmp(a,b);
	printf("%d\n",ret);
	c=ASN1_STRING_dup(a);
	ret=ASN1_STRING_cmp(a,c);
	printf("%d\n",ret);

	ASN1_STRING_free(a);
	ASN1_STRING_free(b);
	ASN1_STRING_free(c);
	return 0;
}

