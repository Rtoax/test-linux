/**
 * https://stackoverflow.com/questions/31437045/how-do-you-programmatically-obtain-a-stack-trace-of-a-child-process-from-its-par
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>
#include <sys/ptrace.h>
#include <libunwind.h>
#include <libunwind-ptrace.h>
#include <signal.h>

#define panic(X) do {	\
		fprintf(stderr, #X "\n");	\
		exit(1);	\
	} while (0)

static unw_addr_space_t addr_space;
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
	int rc = unw_init_remote(&c, addr_space, ui);
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
		unw_get_proc_name(&c, fname, sizeof(fname), &offset);

		printf("\n%p : (%s+0x%x) [%p]\n", (void *)pc, fname,
			(int)offset, (void *)pc);
	} while (unw_step(&c) > 0);

	ptrace(PTRACE_DETACH, child, 0, 0);

	_UPT_destroy(ui);
}

int main(int argc, char **argv, char **envp)
{
	pid_t child;

	addr_space = unw_create_addr_space(&_UPT_accessors, __BYTE_ORDER__);
	if (!addr_space)
		panic("unw_create_addr_space failed");

	child = fork();
	if (!child) {
		char pathname[] = {"./test"};
		execve(pathname, NULL, NULL);
		return 0;
	} else {
		int status;
		struct timespec t = { .tv_sec = 1, .tv_nsec = 0 };
		nanosleep(&t, NULL);

		do_backtrace(child);

		waitpid(child, &status, 0);
	}
	return 0;
}
