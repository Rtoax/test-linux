#include <arm_sve.h>

svuint64_t uaddlb_array(svuint32_t Zs1, svuint32_t Zs2)
{
	/* widening add of even elements */
	svuint64_t result = svaddlb(Zs1, Zs2);
	return result;
}

int main(void)
{
	return 0;
}
