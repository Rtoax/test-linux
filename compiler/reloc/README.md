ELF Relocation Sections
=======================


- `.rel.plt` are `R_386_JUMP_SLOT`
- `.rela.plt` are `R_X86_64_JUMP_SLOT`
- `.rel.dyn` are `R_386_GLOB_DAT`
- `.rela.dyn` are `R_X86_64_GLOB_DAT`


# Links

- https://github.com/ARM-software/abi-aa/blob/main/aaelf64/aaelf64.rst
- https://wiki.osdev.org/ELF_Tutorial
- https://docs.oracle.com/cd/E19120-01/open.solaris/819-0690/6n33n7fct/index.html
- [Hardening ELF binaries using Relocation Read-Only (RELRO)](https://www.redhat.com/en/blog/hardening-elf-binaries-using-relocation-read-only-relro)
- PDF: [System V Application Binary Interface AMD64 Architecture Processor Supplement](https://refspecs.linuxbase.org/elf/x86_64-abi-0.98.pdf)

