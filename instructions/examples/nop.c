int main(void)
{
	while (1) {
		__asm__("nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop\n\t"
			"nop");
	}
	return 0;
}
