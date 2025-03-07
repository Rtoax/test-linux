#include <stdio.h>
#include <stdlib.h>

#include "common.h"


#define ROWS 4
#define COLS 4

#define MATRIX {{1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4},}

/**
 * ref: https://www.intel.com/content/www/us/en/docs/programmable/683152/21-3/example-loop-pipelining-and-unrolling.html
 */
unsigned long __noinline
dut(int rows, int cols)
{
	unsigned long ret = 0;
	int i, j;
	int mRow;

	// store in column-major format
	float a_matrix[COLS][ROWS] = MATRIX;
	// store in row-major format
	float r_matrix[ROWS][COLS] = MATRIX;

	// setup...
	for (j = 0; j < cols; j++) {
		for (mRow = 0; mRow < rows; mRow++) {
			a_matrix[i][mRow] = cols + rows;
			r_matrix[i][mRow] = cols + rows;
		}
	}

	for (i = 0; i < cols; i++) {
		for (j = 0; j < cols; j++) {
			float dotProduct = 0;

			for (mRow = 0; mRow < rows; mRow++) {
				dotProduct += a_matrix[i][mRow] * a_matrix[j][mRow];
			}

			r_matrix[i][j] = (j > i) ? dotProduct : 0; // predication
			ret += r_matrix[i][j];
		}
	}

	return ret;
}

/**
 * FIXME: I don't know how to test loop unrolling with FDO
 */
unsigned long __noinline
l_A(unsigned long a)
{
	unsigned long i, ret = 0;

	for (i = 0; i < a; i++) {
		ret += dut(i % 4, i % 4);
	}

	return ret;
}

unsigned long test_loop(void)
{
	return l_A(0xffffff);
}

int main(int argc, char *argv[])
{
	unsigned long ret = 0;

	start();
	ret = test_loop();
	stop();

	printf("ret = %ld\n", ret);

	return 0;
}
