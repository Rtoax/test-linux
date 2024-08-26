#include <bfd.h>
#include <stdio.h>

int main(void)
{
#if defined(__aarch64__)
	printf("%d : %s\n", BFD_RELOC_AARCH64_JUMP26,
		bfd_get_reloc_code_name(BFD_RELOC_AARCH64_JUMP26));
#elif defined(__x86_64__)
	printf("%d : %s\n", BFD_RELOC_X86_64_GOT32,
		bfd_get_reloc_code_name(BFD_RELOC_X86_64_GOT32));
#else
# warn "Not support arch yet"
#endif
	return 0;
}
