// 将ASN1 数据结构DER 编码，并将结果写入bio。示例如下：
//本程序将ASN1_INTEGER 类型装换为DER 编码并写入文件。int.cer 的内容如下：
//02 01 64 （十六进制）。
//# more int.cer
//d	----> 100 (ASN1_INTEGER_set(a,(long)100);)

#include <openssl/asn1.h>
#include <openssl/bio.h>

int main(void)
{
	int ret;
	BIO *out;
	ASN1_INTEGER *a;

	out = BIO_new_file("int.cer", "w");
	a = ASN1_INTEGER_new();
	ASN1_INTEGER_set(a, (long)100);
	ret = ASN1_i2d_bio(i2d_ASN1_INTEGER, out, a);
	BIO_free(out);
	return 0;
}
