#include <stdio.h>
#include <stdint.h>
#include <arm_neon.h>

void split(uint8_t *rgb, uint8_t *r, uint8_t *g, uint8_t *b)
{
	uint8x16x3_t v = vld3q_u8(rgb);
	vst1q_u8(r, v.val[0]);
	vst1q_u8(g, v.val[1]);
	vst1q_u8(b, v.val[2]);
}

int main(void)
{
	uint8_t rgb[3] = {255, 255, 255};
	uint8_t r, g, b;
	split(rgb, &r, &g, &b);
	printf("r = %d, g = %d, b = %d\n", r, g, b);
	return 0;
}
