#include <ttyent.h>

int main(void)
{
	setttyent();
	endttyent();
	return 0;
}
