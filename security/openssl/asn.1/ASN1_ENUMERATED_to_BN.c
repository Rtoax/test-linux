//BIGNUM *ASN1_ENUMERATED_to_BN(ASN1_ENUMERATED *ai, BIGNUM *bn)
//将ASN1_ENUMERATED 类型转换为BN 大数类型。此函数调用BN_bin2bn 函数
//获取bn，如果ai->type 表明它是负数，再调用BN_set_negative 设置bn 成负数。示例如
//下：
//如果ASN1_ENUMERATED_to_BN 的第二个参数为NULL,bn 将在内部分配空间。
#include <openssl/asn1.h>

int main(void)
{
	long ret;
	ASN1_ENUMERATED *a;
	BIGNUM *bn;

	a = ASN1_ENUMERATED_new();
	ASN1_ENUMERATED_set(a, (long)155);
	ret = ASN1_ENUMERATED_get(a);
	bn = BN_new();
	bn = ASN1_ENUMERATED_to_BN(a,bn);

	BN_free(bn);
	ASN1_ENUMERATED_free(a);
	return 0;
}
