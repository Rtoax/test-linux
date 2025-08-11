int main(void)
{
	/* trigger X86_TRAP_GP */
	asm volatile("cli");
	return 0;
}
