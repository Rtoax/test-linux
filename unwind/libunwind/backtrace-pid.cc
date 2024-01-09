/**
 * https://blog.csdn.net/Morzker/article/details/104436705
 */
#include <iostream>
#include <libunwind.h>
#include <libunwind-ptrace.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <cxxabi.h>
#include <cstdio>


int wait4stop(pid_t pid)
{
	int status = 99;
	do {
		if (waitpid(pid, &status, 0) == -1 || WIFEXITED(status) || WIFSIGNALED(status))
			return 0;
	} while(!WIFSTOPPED(status));
	return 1;
}

void get_backtrace(pid_t pid)
{
	unw_cursor_t cursor, resume_cursor;
	unw_context_t context;
	unw_word_t ip, sp, off;

	unw_addr_space_t addr_space = unw_create_addr_space(&_UPT_accessors, __BYTE_ORDER__);
	if (!addr_space) {
		std::cerr << "Failed to create address space" << std::endl;
		exit(1);
	}

	unw_getcontext(&context);

	if (-1 == ptrace(PTRACE_ATTACH, pid, nullptr, nullptr))
		std::cerr << "Failed to ptrace" << std::endl;

	if (!wait4stop(pid))
		std::cerr << "wait SIGSTOP of ptrace failed" << std::endl;

	void *rctx = _UPT_create(pid);

	if (rctx == nullptr)
		std::cerr << "Failed to _UPT_create" << std::endl;

	if (unw_init_remote(&cursor, addr_space, rctx))
		std::cerr << "unw_init_remote failed" << std::endl;

	resume_cursor = cursor;

	const size_t bufflen = 256;
	char *buff = new char[bufflen];

	do {
		char *name;
		unw_get_reg(&cursor, UNW_REG_IP, &ip);
		unw_get_reg(&cursor, UNW_REG_SP, &sp);

		/* 获取函数名字 */
		if (0 == unw_get_proc_name(&cursor, buff, bufflen, &off)) {
			int status = 99;
			printf("%s---", buff);
			/* 如果符号表中没有找到buff的函数名 */
			if ((name = abi::__cxa_demangle(buff, nullptr, nullptr, &status)) == 0)
				name = buff;
		}
		printf("%s.\n", name);
	} while (unw_step(&cursor) > 0);

	delete[] buff;
	_UPT_resume(addr_space, &resume_cursor, rctx);
	_UPT_destroy(rctx);

	/* 然后是将进程结束中断 */
	ptrace(PTRACE_DETACH, pid, nullptr, nullptr);
}

int main(void)
{
	pid_t child = fork();
	if (!child) {
		char pathname[] = {"./test"};
		execve(pathname, NULL, NULL);
		return 0;
	} else {
		int status;
		struct timespec t = { .tv_sec = 1, .tv_nsec = 0 };
		nanosleep(&t, NULL);
		get_backtrace(child);
		waitpid(child, &status, 0);
	}
	return 0;
}
