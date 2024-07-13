// 将整数转换成为ASCII 码,放在BIO 中。示例如下：
//输出:
//输入v 的值:
//15
//0F
#include <openssl/asn1.h>

int main(void)
{
	ASN1_INTEGER *i;
	long v;
	BIO *bp;
	printf("输入v 的值:\n");
	scanf("%ld",&v);
	i=ASN1_INTEGER_new();
	ASN1_INTEGER_set(i,v);
	bp=BIO_new(BIO_s_file());
	BIO_set_fp(bp,stdout,BIO_NOCLOSE);
	i2a_ASN1_INTEGER(bp,i);
	BIO_free(bp);
	ASN1_INTEGER_free(i);
	printf("\n");
	return 0;
}
