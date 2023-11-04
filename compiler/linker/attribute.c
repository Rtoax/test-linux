const char interp[] __attribute__((section(".interp"))) = "/usr/bin/ld";

int main(void)
{
	return 0;
}

void _start(void)
{
	main();
}
