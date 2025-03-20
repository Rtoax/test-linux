#include <stdio.h>
#include <iconv.h>
#include <errno.h>
#include <string.h>

/* Hello, world! */
static char in_utf16le_buf[] = {
	0x48, 0x00, 0x65, 0x00, 0x6C, 0x00, 0x6C, 0x00, 0x6F, 0x00,
	0x2C, 0x00, 0x20, 0x00, 0x77, 0x00, 0x6F, 0x00, 0x72, 0x00,
	0x6C, 0x00, 0x64, 0x00, 0x21, 0x00, 0x00, 0x00
};

void utf16le_to_utf8(void)
{
	int err;
	iconv_t icv;
	char outbuff[sizeof(in_utf16le_buf) / 2 + 1];
	char *in, *out;
	size_t inbytes, outbytes = sizeof(outbuff);

	icv = iconv_open("UTF-8", "UTF-16LE");
	if (icv == (iconv_t)-1) {
		perror("iconv_open");
		return;
	}

	in = in_utf16le_buf;
	out = outbuff;
	inbytes = sizeof(in_utf16le_buf);

	err = iconv(icv, &in, &inbytes, &out, &outbytes);
	if (err)
		perror("iconv");

	*out = '\0';

	printf("out %s\n", outbuff);

	iconv_close(icv);
}

int main(void)
{
	utf16le_to_utf8();
	return 0;
}
