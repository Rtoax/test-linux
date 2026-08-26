#pragma once

#define __weak_alias(name) __attribute__((weak, alias(name)))

#define weak_alias(name, aliasname) \
	extern typeof(name) aliasname __attribute__((weak, alias(#name)))
