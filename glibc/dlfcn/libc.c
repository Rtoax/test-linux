#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <sys/un.h>
#include <netinet/in.h>

#define __USE_GNU
#include <dlfcn.h>
#include <unistd.h>


typedef int (*socket_pfn_t)(int domain, int type, int protocol);

static socket_pfn_t g_sys_socket_func = NULL;

#define HOOK_SYS_FUNC(name) \
	if ( !g_sys_##name##_func ) { \
		g_sys_##name##_func = (name##_pfn_t)dlsym(RTLD_NEXT, #name); \
	}

void __attribute__((constructor(101))) __dlsym_sys_func_init(void)
{
	g_sys_socket_func = (socket_pfn_t)dlsym(RTLD_NEXT, "socket");
}

int socket(int domain, int type, int protocol)
{
	HOOK_SYS_FUNC(socket);
	printf("call socket.\n");
	return g_sys_socket_func(domain, type, protocol);
}

