#include <stdio.h>
#include <glob.h>
#include <unistd.h>


int main(void)
{
	glob_t globbuf;

	/**
	 * ls -l *.c ../\*.c
	 */
	globbuf.gl_offs = 2;
	glob("*.c", GLOB_DOOFFS, NULL, &globbuf);
	glob("../*.c", GLOB_DOOFFS | GLOB_APPEND, NULL, &globbuf);
	globbuf.gl_pathv[0] = "ls";
	globbuf.gl_pathv[1] = "-l";
	execvp("ls", &globbuf.gl_pathv[0]);
}
