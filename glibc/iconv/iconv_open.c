#include <stdio.h>
#include <iconv.h>
#include <wchar.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	iconv_t icv = iconv_open("utf-8", "gb2312");
	iconv_close(icv);
	return 0;
}
