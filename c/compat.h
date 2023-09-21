#pragma once

#define ___deprecated_cat(A, B) A ## B
#define ___deprecated_select(NAME, NUM) ___deprecated_cat(NAME, NUM)
#define ___deprecated_nth(_1, _2, _3, _4, _5, _6, N, ...) N
#define ___deprecated_cnt(...) ___deprecated_nth(__VA_ARGS__, 6, 5, 4, 3, 2, 1)
#define ___deprecated_overload(NAME, ...) \
		___deprecated_select(NAME, ___deprecated_cnt(__VA_ARGS__))(__VA_ARGS__)

int prog_load_deprecated(int a, int b, int c, int d);
int prog_load(int a, int b, int c, int d, int e, int f);

#ifndef prog_load
#define prog_load(...) ___deprecated_overload(___prog_load, __VA_ARGS__)
#define ___prog_load4(file, type, pobj, prog_fd) \
		prog_load_deprecated(file, type, pobj, prog_fd)
#define ___prog_load6(prog_type, prog_name, license, insns, insn_cnt, opts) \
		prog_load(prog_type, prog_name, license, insns, insn_cnt, opts)
#endif /* prog_load */

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

#else /* !SHARED */

#define COMPAT_VERSION(internal_name, api_name, version)
#define DEFAULT_VERSION(internal_name, api_name, version) \
		extern typeof(internal_name) api_name \
		__attribute__((alias(#internal_name)));
#endif
