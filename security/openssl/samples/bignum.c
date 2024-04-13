#include <string.h>
#include <openssl/bio.h>
#include <openssl/bn.h>

int main(void)
{
	BIGNUM *bn;
	BIO *b;
	char a[20];

	bn = BN_new();
	strcpy(a, "32");
	BN_hex2bn(&bn, a);
	b = BIO_new(BIO_s_file());

	BIO_set_fp(b, stdout, BIO_NOCLOSE);

	BIO_write(b, "aaa", 3);
	BN_print(b, bn);

	BN_free(bn);

	return 0;
}

