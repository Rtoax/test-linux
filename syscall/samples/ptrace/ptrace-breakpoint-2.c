/**
 * x86 breakpoint
 *
 * 2020-12-21	Rong Tao	Create this
 */
#include <stdio.h>
#include <stddef.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/prctl.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>

typedef enum {
	DATA_BREAK,
	CMD_BREAK,
} break_type;

enum {
	BREAK_LOCAL = 0x1,
	BREAK_GLOBAL = 0x10,
};

enum {
	BREAK_EXEC = 0x0,
	BREAK_WRITE = 0x1,
	BREAK_RDWR = 0x3,
};

enum {
	BREAK_BYTE = 0x0,
	BREAK_WORD = 0x1,
	BREAK_DWORD = 0x3,
};

#define ENABLE_BREAKPOINT(x) (BREAK_LOCAL << (x * 2))

#define BREAK_TYPE_EXEC(x) (BREAK_EXEC << (16 + (x * 4)))
#define BREAK_TYPE_WRITE(x) (BREAK_WRITE << (16 + (x * 4)))
#define BREAK_TYPE_RDWR(x) (BREAK_RDWR << (16 + (x * 4)))

#define BREAK_LEN_BYTE(x) (BREAK_BYTE << (18 + (x * 4)))
#define BREAK_LEN_WORD(x) (BREAK_WORD << (18 + (x * 4)))
#define BREAK_LEN_DWORD(x) (BREAK_DWORD << (18 + (x * 4)))

/*
 * This function fork()s a child that will use
 * ptrace to set a hardware breakpoint for
 * memory r/w at _addr_. When the breakpoint is
 * hit, then _handler_ is invoked in a signal-
 * handling context.
 */
bool set_breakpoint(void *addr, int bpno, void (*handler)(int), break_type type)
{
	pid_t child = 0;
	uint32_t enable_breakpoint = ENABLE_BREAKPOINT(bpno);
	uint32_t enable_breakwrite;
	uint32_t break_len;

	switch (type) {
	case DATA_BREAK:
		/* 数据断点这里可以自定义 */
		enable_breakwrite = BREAK_TYPE_WRITE(bpno);
		break_len = BREAK_LEN_DWORD(bpno);
		break;
	case CMD_BREAK:
		/* 指令断点这里必须为 0, 即 执行 和 1字节 */
		enable_breakwrite = BREAK_TYPE_EXEC(bpno);
		break_len = BREAK_LEN_BYTE(bpno);
		break;
	}

	pid_t parent = getpid();
	int child_status = 0;

	if (!(child = fork())) {
		int parent_status = 0;
		if (ptrace(PTRACE_ATTACH, parent, NULL, NULL))
			_exit(1);

		while (!WIFSTOPPED(parent_status))
			waitpid(parent, &parent_status, 0);

		/*
		 * set the breakpoint address.
		 */
		if (ptrace(PTRACE_POKEUSER,
			   parent,
			   offsetof(struct user, u_debugreg[bpno]), addr))
			 _exit(1);

		/*
		 * set parameters for when the breakpoint should be triggered.
		 */
		if (ptrace(PTRACE_POKEUSER,
			   parent,
			   offsetof(struct user, u_debugreg[7]),
			   enable_breakwrite | enable_breakpoint | break_len))
			 _exit(1);

		if (ptrace(PTRACE_DETACH, parent, NULL, NULL))
			_exit(1);

		_exit(0);
	}

	waitpid(child, &child_status, 0);

	/**
	 * 子进程断点，处理子进程的 SIGTRAP 信号
	 */
	signal(SIGTRAP, handler);

	if (WIFEXITED(child_status) && !WEXITSTATUS(child_status))
		return true;
	return false;
}

/*
 * This function will disable a breakpoint by
 * invoking set_breakpoint is a 0x0 _addr_
 * and no handler function. See comments above
 * for implementation details.
 */
bool del_breakpoint(int bpno, break_type type)
{
	return set_breakpoint(0x0, bpno, NULL, type);
}

void do_foo(void)
{
}

/*
 * Example of how to use this /library/.
 */
int handled_sigtrap = 0;

void handle_sigtrap(int s)
{
	handled_sigtrap += 1;
	return;
}

int main(int argc, char **argv)
{
	int i;
	int16_t a[3] = { 0 };
	break_type bp_type = CMD_BREAK;

	if (!set_breakpoint(do_foo, 0, handle_sigtrap, bp_type))
		printf("failed to set the breakpoint!\n");

	for (i = 0; i < 12321; i++) {
		do_foo();
	}
	if (!del_breakpoint(0, bp_type))
		printf("failed to disable the breakpoint!\n");

	if (!set_breakpoint(a, 1, handle_sigtrap, DATA_BREAK))
		printf("failed to set the breakpoint!\n");

	for (i = 0; i < 12321; i++) {
		a[0] = 1;
		a[1] = 1;
		a[2] = 1;
	}

	if (!del_breakpoint(0, bp_type))
		printf("failed to disable the breakpoint!\n");

	printf("handled_sigtrap: %d\n", handled_sigtrap);

	return 1;
}
