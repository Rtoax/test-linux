#pragma once

#define ___deprecated_cat(A, B) A ## B
#define ___deprecated_select(NAME, NUM) ___deprecated_cat(NAME, NUM)
#define ___deprecated_nth(_1, _2, _3, _4, _5, _6, N, ...) N
#define ___deprecated_cnt(...) ___deprecated_nth(__VA_ARGS__, 6, 5, 4, 3, 2, 1)
#define ___deprecated_overload(NAME, ...) \
		___deprecated_select(NAME, ___deprecated_cnt(__VA_ARGS__))(__VA_ARGS__)

int foo_v1(int a, int b, int c, int d);
int foo_v2(int a, int b, int c, int d, int e, int f);

#ifndef foo
#define foo(...) ___deprecated_overload(___foo, __VA_ARGS__)
#define ___foo4(a, b, c, d) foo_v1(a, b, c, d)
#define ___foo6(a, b, c, d, e, f) foo_v2(a, b, c, d, e, f)
#endif

#define SHARED

#if defined(SHARED) && defined(__GNUC__) && __GNUC__ >= 10

#define DEFAULT_VERSION(internal_name, api_name, version) \
		__attribute__((symver(#internal_name "@@" #version)))
#define COMPAT_VERSION(internal_name, api_name, version) \
		__attribute__((symver(#internal_name "@" #version)))

#elif defined(SHARED)

#define COMPAT_VERSION(internal_name, api_name, version) \
		asm(".symver " #internal_name "," #api_name "@" #version);
#define DEFAULT_VERSION(internal_name, api_name, version) \
		asm(".symver " #internal_name "," #api_name "@@" #version);

#else				/* !SHARED */

#define COMPAT_VERSION(internal_name, api_name, version)
#define DEFAULT_VERSION(internal_name, api_name, version) \
		extern typeof(internal_name) api_name \
		__attribute__((alias(#internal_name)));
#endif
