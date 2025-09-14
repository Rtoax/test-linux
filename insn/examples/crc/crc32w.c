/**
 *
 * Refs:
 * 1. https://stackoverflow.com/questions/47202725/what-does-arm-crc32w-do
 */
#include <stdio.h>
#include <stdint.h>

int main()
{
	uint32_t crc=0xFFFFFFFF; 
	uint32_t val=100;
	asm volatile("crc32w %w0, %w0, %w1": "+r" (crc): "r" (val)  );
}
