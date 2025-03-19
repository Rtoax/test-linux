#include <stdio.h>
#include <iconv.h>
#include <wchar.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	int err;
	iconv_t icv;
	char inbuff[] = { 't', '\0', 'e', '\0', 's', '\0', 't', '\0' };
	char outbuff[64];
	char *in, *out;
	size_t inbytes, outbytes = sizeof(outbuff);

	icv = iconv_open("UTF-8", "UTF-16LE");
	if (icv == (iconv_t)-1) {
		perror("iconv_open");
		return errno;
	}

	in = inbuff;
	out = outbuff;
	inbytes = sizeof(inbuff);

	err = iconv(icv, &in, &inbytes, &out, &outbytes);
	if (err)
		perror("iconv");

	printf("in  %s\n", in);
	printf("out %s\n", out);

	iconv_close(icv);

	return 0;
}
