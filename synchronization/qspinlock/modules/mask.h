#pragma once

static const unsigned char *binary32(u32 v)
{
	static unsigned char s[33] = {0};
	int i;
	for (i = 0; i < 32; i++)
		s[31 - i] = '0' + !!(v & (1UL << i));
	s[32] = '\0';
	return s;
}
