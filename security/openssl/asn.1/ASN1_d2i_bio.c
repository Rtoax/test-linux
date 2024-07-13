//void *ASN1_d2i_bio(void *(*xnew)(void), d2i_of_void *d2i, BIO *in, void **x)
//对bio 的数据DER 解码，xnew 无意义，d2i 为DER 解码函数，in 为bio 数据，x
//为数据类型，返回值为解码后的结果。如果x 分配了内存，x 所指向的地址与返回值一
//致。示例如下：
#include <stdio.h>
#include <openssl/asn1.h>
#include <openssl/x509v3.h>
#include <openssl/bio.h>

int main(void)
{
	BIO *in;
	X509 **out=NULL,*x;
	in=BIO_new_file("a.cer","r");
	out=(X509 **)malloc(sizeof(X509 *));
	*out=NULL;
	x=ASN1_d2i_bio(NULL,(d2i_of_void *)d2i_X509,in,(void**)out);
	X509_free(x);
	free(out);
	return 0;
}

