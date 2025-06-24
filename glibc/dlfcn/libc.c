#include <stdio.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <sys/un.h>
#include <netinet/in.h>

#ifndef __USE_GNU
#define __USE_GNU
#endif
#include <dlfcn.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

#include "common.h"


#define LIBC_SO "libc.so.6" /* /usr/lib64/libc.so.6 */

static __thread bool override = false;

typedef int (*socket_fn_t)(int domain, int type, int protocol);

typedef void *(*malloc_fn_t)(size_t size);
typedef void  (*free_fn_t)(void *ptr);
typedef void *(*calloc_fn_t)(size_t nmemb, size_t size);
typedef void *(*realloc_fn_t)(void *ptr, size_t size);

typedef char *(*strdup_fn_t)(const char *s);
typedef char *(*strndup_fn_t)(const char *s, size_t n);

static socket_fn_t      g_sys_socket_func = NULL;
static malloc_fn_t      g_sys_malloc_func = NULL;
static free_fn_t        g_sys_free_func = NULL;
static calloc_fn_t      g_sys_calloc_func = NULL;
static realloc_fn_t     g_sys_realloc_func = NULL;
static strdup_fn_t      g_sys_strdup_func = NULL;
static strndup_fn_t     g_sys_strndup_func = NULL;

static socket_fn_t      g_libc_real_socket_func = NULL;
static malloc_fn_t      g_libc_real_malloc_func = NULL;
static free_fn_t        g_libc_real_free_func = NULL;
static calloc_fn_t      g_libc_real_calloc_func = NULL;
static realloc_fn_t     g_libc_real_realloc_func = NULL;
static strdup_fn_t      g_libc_real_strdup_func = NULL;
static strndup_fn_t     g_libc_real_strndup_func = NULL;


static void *__libc_dl_handle = RTLD_NEXT;

#define HOOK_SYS_FUNC(name) \
	if ( !g_sys_##name##_func ) { \
		g_sys_##name##_func = (name##_fn_t)dlsym(__libc_dl_handle, #name); \
		if (!g_sys_##name##_func) { \
			fprintf(stderr, "Failed to load %s\n", #name); \
		} \
	}

#define HOOK_LIBC_FUNC(name, dl) \
	if( !g_libc_real_##name##_func ) { \
		g_libc_real_##name##_func = (name##_fn_t)dlsym(dl, #name); \
		if (!g_libc_real_##name##_func) { \
			fprintf(stderr, "Failed to load %s\n", #name); \
		} \
	}

static void __sys_libc(void)
{
	HOOK_SYS_FUNC(socket);
	HOOK_SYS_FUNC(malloc);
	HOOK_SYS_FUNC(free);
	HOOK_SYS_FUNC(calloc);
	HOOK_SYS_FUNC(realloc);
	HOOK_SYS_FUNC(strdup);
	HOOK_SYS_FUNC(strndup);
}

static void __real_libc(void)
{
	void *libc = dlopen(LIBC_SO, RTLD_LAZY | RTLD_LOCAL | RTLD_NOLOAD);
	if (!libc) {
		fprintf(stderr, "Failed to find "LIBC_SO", %s\n", strerror(errno));
		return;
	}
	HOOK_LIBC_FUNC(socket, libc);
	HOOK_LIBC_FUNC(malloc, libc);
	HOOK_LIBC_FUNC(free, libc);
	HOOK_LIBC_FUNC(calloc, libc);
	HOOK_LIBC_FUNC(realloc, libc);
	HOOK_LIBC_FUNC(strdup, libc);
	HOOK_LIBC_FUNC(strndup, libc);
}

void __attribute__((constructor(101))) __dlsym_sys_func_init(void)
{
	override = false;

	__sys_libc();
	__real_libc();
}

void libc_override_set(bool state)
{
	override = state;
}

bool libc_override_get(void)
{
	return override;
}

static int __socket(int domain, int type, int protocol)
{
	debug();
	return 0;
}

int socket(int domain, int type, int protocol)
{
	if (override)
		return __socket(domain, type, protocol);
	return g_sys_socket_func(domain, type, protocol);
}

void *malloc(size_t size)
{
	if (g_sys_malloc_func) {
		return g_sys_malloc_func(size);
	}
	if (g_libc_real_malloc_func) {
		return g_libc_real_malloc_func(size);
	}
	return NULL;
}

void free(void *ptr)
{
	if (g_sys_free_func) {
		g_sys_free_func(ptr);
		return;
	}
	if (g_libc_real_free_func) {
		g_libc_real_free_func(ptr);
		return;
	}
	return;
}

void *calloc(size_t nmemb, size_t size)
{
	if (g_sys_calloc_func) {
		return g_sys_calloc_func(nmemb, size);
	}
	if (g_libc_real_calloc_func) {
		return g_libc_real_calloc_func(nmemb, size);
	}
	return NULL;
}

void *realloc(void *ptr, size_t size)
{
	if (g_sys_realloc_func) {
		return g_sys_realloc_func(ptr, size);
	}
	if (g_libc_real_realloc_func) {
		return g_libc_real_realloc_func(ptr, size);
	}
	return NULL;
}

char *strdup(const char *s)
{
	if (g_sys_strdup_func) {
		return g_sys_strdup_func(s);
	}
	if (g_libc_real_strdup_func) {
		return g_libc_real_strdup_func(s);
	}
	return NULL;
}

char *strndup(const char *s, size_t n)
{
	if (g_sys_strndup_func) {
		return g_sys_strndup_func(s, n);
	}
	if (g_libc_real_strndup_func) {
		return g_libc_real_strndup_func(s, n);
	}
	return NULL;
}

