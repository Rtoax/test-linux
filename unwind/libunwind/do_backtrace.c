/**
 *
 *	https://stackoverflow.com/questions/31437045/how-do-you-programmatically-obtain-a-stack-trace-of-a-child-process-from-its-par
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>
#include <sys/ptrace.h>
#define UNW_LOCAL_ONLY
#include <libunwind.h>
#include <libunwind-ptrace.h>
#include <libunwind-x86_64.h>
#include <signal.h>

#define panic(X) fprintf(stderr, #X "\n");

static unw_addr_space_t as;
static struct UPT_info *ui;

void do_backtrace(pid_t child)
{

	ui = _UPT_create(child);
	if (!ui) {
		panic("_UPT_create failed");
	}

	ptrace(PTRACE_ATTACH, child, 0, 0);
	struct timespec t = { .tv_sec = 0, t.tv_nsec = 1000000 };
	nanosleep(&t, NULL);

	unw_cursor_t c;
	int rc = unw_init_remote(&c, as, ui);
	if (rc != 0) {
		if (rc == UNW_EINVAL) {
			panic("unw_init_remote: UNW_EINVAL");
		} else if (rc == UNW_EUNSPEC) {
			panic("unw_init_remote: UNW_EUNSPEC");
		} else if (rc == UNW_EBADREG) {
			panic("unw_init_remote: UNW_EBADREG");
		} else {
			panic("unw_init_remote: UNKNOWN");
		}
	}

	do {
		unw_word_t  offset, pc;
		char        fname[64];

		unw_get_reg(&c, UNW_REG_IP, &pc);
		fname[0] = '\0';
		(void) unw_get_proc_name(&c, fname, sizeof(fname), &offset);

		printf("\n%p : (%s+0x%x) [%p]\n",
			   (void *)pc, fname, (int) offset, (void *) pc);
	} while (unw_step(&c) > 0);


	ptrace(PTRACE_DETACH, child, 0, 0);

	_UPT_destroy(ui);
}


int main(int argc __attribute__((unused)), char **argv, char **envp)
{
	as = unw_create_addr_space(&_UPT_accessors, 0);
	if (!as) {
		panic("unw_create_addr_space failed");
	}

	pid_t child;
	child = fork();

	if (!child) {

		execve("/home/#######/#######/my_utilities/child_bt/cg.A.x",
				argv, envp);

		return 0;

	} else {

		struct timespec t = { .tv_sec = 1, .tv_nsec = 0 };
		nanosleep(&t, NULL);

		do_backtrace(child);

		int status;
		waitpid(child, &status, 0);

	}

	return 0;
}
