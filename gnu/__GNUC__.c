/**
 * The __GNUC__ symbol is defined in the GCC repository.
 *
 * gcc::gcc/cppbuiltin.cc: define__GNUC__()
 * llvm::clang/lib/Frontend/InitPreprocessor.cpp: InitializePredefinedMacros()
 */

#include <stdio.h>

#if defined(__GNUC__) && ((__GNUC__ == 4) && (__GNUC_MINOR__ >= 5) || __GNUC__ >= 5)
/* do some check */
#endif

#if !__GNUC_PREREQ(__GNUC__, __GNUC_MINOR__)
# error "__GNUC_PREREQ() failed"
#endif


int main(void)
{
	const char *pfx = "gcc";
#ifdef __clang__
	pfx = "clang";

	printf("%s: __clang_major__ = %d\n", pfx, __clang_major__);
	printf("%s: __clang_minor__ = %d\n", pfx, __clang_minor__);
	printf("%s: __clang_patchlevel__ = %d\n", pfx, __clang_patchlevel__);
	printf("%s: __clang_version__ = %s\n", pfx, __clang_version__);
#endif

#ifdef __NVCC__	/* Nvidia nvcc */
	pfx = "nvcc";
	printf("%s: __NVCC__ = %d\n", pfx, __NVCC__);
#endif
#ifdef __HPCC__	/* MetaX htcc */
	pfx = "htcc";
	printf("%s: __HPCC__ = %d\n", pfx, __HPCC__);
#endif

	printf("%s: __GNUC__ = %d.\n", pfx, __GNUC__);
	printf("%s: __GNUC_MINOR__ = %d.\n", pfx, __GNUC_MINOR__);
	printf("%s: __GNUC_PATCHLEVEL__ = %d.\n", pfx, __GNUC_PATCHLEVEL__);

	/**
	 * macros for the C11 / C++11 memory orderings
	 *
	 * gcc::gcc/cppbuiltin.cc: define__GNUC__()
	 * llvm::clang/lib/Frontend/InitPreprocessor.cpp: InitializePredefinedMacros()
	 */
	printf("%s: __ATOMIC_RELAXED = %d.\n", pfx, __ATOMIC_RELAXED);
	printf("%s: __ATOMIC_SEQ_CST = %d.\n", pfx, __ATOMIC_SEQ_CST);
	printf("%s: __ATOMIC_ACQUIRE = %d.\n", pfx, __ATOMIC_ACQUIRE);
	printf("%s: __ATOMIC_RELEASE = %d.\n", pfx, __ATOMIC_RELEASE);
	printf("%s: __ATOMIC_ACQ_REL = %d.\n", pfx, __ATOMIC_ACQ_REL);
	printf("%s: __ATOMIC_CONSUME = %d.\n", pfx, __ATOMIC_CONSUME);

	/* This macro expands to a string constant which describes the version
	 * of the compiler in use. You should not rely on its contents having
	 * any particular form, but it can be counted on to contain at least
	 * the release number. */
	printf("%s: __VERSION__ = %s\n", pfx, __VERSION__);

#ifdef __CUDA__
	printf("%s: __CUDA__ = %d\n", pfx, __CUDA__);
#endif
#ifdef __CUDACC__
	printf("%s: __CUDACC__ = %d\n", pfx, __CUDACC__);
#endif
#ifdef __CUDA_ARCH__
	printf("%s: __CUDA_ARCH__ = %d\n", pfx, __CUDA_ARCH__);
#endif
#ifdef __CUDACC_VER_MAJOR__
	printf("%s: __CUDACC_VER_MAJOR__ = %d\n", pfx, __CUDACC_VER_MAJOR__);
	printf("%s: __CUDACC_VER_MINOR__ = %d\n", pfx, __CUDACC_VER_MINOR__);
	printf("%s: __CUDACC_VER_BUILD__ = %d\n", pfx, __CUDACC_VER_BUILD__);
#endif

#ifdef __HPCC_ARCH__
	printf("%s: __HPCC_ARCH__ = %d\n", pfx, __HPCC_ARCH__);
#endif

	return 0;
}
