/**
 * R_AARCH64_PREL64
 * R_AARCH64_PREL32 (like R_X86_64_PC32)
 * R_AARCH64_PREL16
 */
#include <stdio.h>
#include <stdint.h>

/**
 * foo, bar is R_AARCH64_PREL32 in ELF 64-bit LSB relocatable
 */
void foo(void) {}
void bar(void) {}

/**
 * main is R_AARCH64_PREL32
 */
int main(void)
{
	return 0;
}
