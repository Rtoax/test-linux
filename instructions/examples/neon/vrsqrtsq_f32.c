#include <arm_neon.h>

inline float32x4_t vsqrt(float32x4_t v)
{
	//求得开方倒数的初始估计值
	float32x4_t r = vrsqrteq_f32(v);
	//逼近
	r = vmulq_f32(vrsqrtsq_f32(v, r), r);
	//通过乘法转为开方
	return vmulq_f32(v, r);
}

int main(void)
{
	return 0;
}
