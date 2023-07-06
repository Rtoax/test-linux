#pragma once

#define f_weak_alias(name) \
	__attribute__((weak, alias(name)))

#define weak_alias(name, aliasname) \
	extern typeof (name) aliasname __attribute__ ((weak, alias(#name)))

