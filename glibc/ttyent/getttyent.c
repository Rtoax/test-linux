#include <stdio.h>
#include <ttyent.h>

int main(void)
{
	struct ttyent *ent;

	setttyent();

	while ((ent = getttyent())) {
		printf("%s\n", ent->ty_name);
	}

	endttyent();
	return 0;
}
