#define _frame_pointer	__attribute__((optimize("omit-frame-pointer")))

_frame_pointer int foo(void)
{
	int i = 0;
	return i + 1;
}

int main(void)
{
	return foo();
}