#pragma once

static const unsigned char *binary32(char *buf, unsigned int buf_size, u32 v)
{
	int i;
	char *s = buf;
	if (buf_size < 33)
		return NULL;

	for (i = 0; i < 32; i++)
		s[31 - i] = '0' + !!(v & (1UL << i));
	s[32] = '\0';
	return s;
}

static const unsigned char *binary32_unsafe(u32 v)
{
	static unsigned char s[33] = {0};
	return binary32(s, 33, v);
}
