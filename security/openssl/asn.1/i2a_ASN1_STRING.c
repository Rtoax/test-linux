//int i2a_ASN1_STRING(BIO *bp, ASN1_STRING *a, int type)
//type 不起作用，将ASN1_STRING 转换为ASCII 码.。示例如下：
//输出结果:
//B2E2CAD4
//我的输出是
//# ./a.out
//		E6B58BE8
#include <openssl/asn1.h>
#include <openssl/asn1t.h>

int main(void)
{
	ASN1_STRING *a;
	BIO *bp;

	a = ASN1_STRING_new();
	ASN1_STRING_set(a, "测试", 4);
	bp = BIO_new(BIO_s_file());
	BIO_set_fp(bp, stdout, BIO_NOCLOSE);
	i2a_ASN1_STRING(bp, a, 1);
	BIO_free(bp);
	ASN1_STRING_free(a);
	printf("\n");
	return 0;
}