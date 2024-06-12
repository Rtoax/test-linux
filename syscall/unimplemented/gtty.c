#include <stdio.h>
#include <sgtty.h>
#include <stdlib.h>

struct sgttyb_self {
	char sg_ispeed;
	char sg_ospeed;
	char sg_erase;
	char sg_kill;
	int sg_flags;
};

int main(void)
{
	struct sgttyb_self st;

	gtty(fileno(stdout),(struct sgttyb *)&st);

	printf("%c, %c, %c, %c, %d\n", st.sg_ispeed, st.sg_ospeed, st.sg_erase,
		st.sg_kill, st.sg_flags);

	return 0;
}
