#include <stdio.h>
#include <stdint.h>
#include <arm_neon.h>

int main(void)
{
	size_t i;
	double Val1[4] = { 2.46574621, 0.46546221, 3.14, 1.23 };
	double Val2[4] = { 2.63565654, 0.46574621, 3.14, 1.23 };
	double Sum[4] = { 0.0, 0.0, 0.0, 0.0 };
	double Sum_C[4] = { 0.0, 0.0, 0.0, 0.0 };

	for (i = 0; i < 4; i += 2) {
		float64x2_t f1 = vld1q_f64(&(Val1[i]));
		float64x2_t f2 = vld1q_f64(&(Val2[i]));
		float64x2_t sum = vaddq_f64(f1, f2);
		vst1q_f64(&Sum[i], sum);
	}

	for (i = 0; i < 4; i++) {
		Sum_C[i] = Val1[i] + Val2[i];
		if (Sum_C[i] != Sum[i])
			printf("[Error]   Sum %lf != %lf\n", Sum[i], Sum_C[i]);
		else
			printf("[Passed]  Sum %lf == %lf\n", Sum[i], Sum_C[i]);
	}
	return 0;
}
