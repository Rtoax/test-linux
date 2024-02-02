#include <stdio.h>
#include <gnu/lib-names.h>

int main (void)
{
#define P(M)	printf("%32s : ", #M); puts(M);
#if defined(__x86_64__)
	P(LD_LINUX_X86_64_SO);
#elif defined(__aarch64__)
	puts(LD_LINUX_AARCH64_SO);
#endif
	P(LD_SO);
	P(LIBANL_SO);
	P(LIBBROKENLOCALE_SO);
	P(LIBCRYPT_SO);
	P(LIBC_MALLOC_DEBUG_SO);
	P(LIBC_SO);
	P(LIBDL_SO);
	P(LIBGCC_S_SO);
	P(LIBMVEC_SO);
	P(LIBM_SO);
	P(LIBNSL_SO);
	P(LIBNSS_COMPAT_SO);
	P(LIBNSS_DB_SO);
	P(LIBNSS_DNS_SO);
	P(LIBNSS_FILES_SO);
	P(LIBNSS_HESIOD_SO);
	P(LIBNSS_LDAP_SO);
	P(LIBPTHREAD_SO);
	P(LIBRESOLV_SO);
	P(LIBRT_SO);
	P(LIBTHREAD_DB_SO);
	P(LIBUTIL_SO);
	return 0;
}
