#ifdef TEST_ATTRIBUTE
#define __example	__attribute__(("example"))
#else
#define __example
#endif

__example int main(void)
{
	return 0;
}
