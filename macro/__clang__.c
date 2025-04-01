/**
 * llvm::clang/lib/Frontend/InitPreprocessor.cpp: InitializePredefinedMacros()
 */
#include <stdio.h>

int main(void)
{
#ifdef __llvm__
	printf("llvm:\n");
#endif
#ifdef __clang__
	printf("clang:\n");
	printf("clang: __clang_major__ = %d\n", __clang_major__);
	printf("clang: __clang_minor__ = %d\n", __clang_minor__);
	printf("clang: __clang_patchlevel__ = %d\n", __clang_patchlevel__);
	printf("clang: __clang_version__ = %s\n", __clang_version__);
#else
	printf("not define __clang__, please compile with clang.\n");
#endif
	return 0;
}
