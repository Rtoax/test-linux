#include <stdio.h>
#include <stdlib.h>
#include <shadow.h>
#include <errno.h>


void display_spwd(struct spwd *spwd)
{
#define LS(v)	printf("%32s = %s\n", #v, spwd->v)
#define LI(v)	printf("%32s = %ld\n", #v, spwd->v)
	LS(sp_namp);
	LS(sp_pwdp);
	LI(sp_lstchg);
	LI(sp_min);
	LI(sp_max);
	LI(sp_warn);
	LI(sp_inact);
	LI(sp_expire);
	LI(sp_flag);
#undef LS
#undef LI
}

int main(int argc, char *argv[])
{
	struct spwd *spwd = getspent();
	if (!spwd) {
		/* FIXME: getspent should set errno??? */
		errno = EPERM;
		fprintf(stderr, "getspent: %m\n");
		exit(EXIT_FAILURE);
	}

	display_spwd(spwd);

	return 0;
}

