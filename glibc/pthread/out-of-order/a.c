/**
 * https://gcc.gnu.org/wiki/Atomic/GCCMM/AtomicSync
 */

int a, b, x, y;

void *task1(void *unused)
{
	x = a;
	y = b;
	/**
	 * looks like an infinite loop
	 */
	while (a == x);
}

void *task2(void *unused)
{
	while (y != b);
	a = 1;
}

int main(void)
{
	x = 0;
	y = 0;
	a = 0;
	b = 1;

	return 0;
}
