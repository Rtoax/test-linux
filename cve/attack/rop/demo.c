int func(void)
{
	int b[1];
	b[0] = 0x90909090;
	b[1] = 0x90909090;
	b[2] = 0x90909090;
	b[3] = 0x90909090; /* Overwrite return value */
}

int main(void)
{
	func();
	return 0;
}
