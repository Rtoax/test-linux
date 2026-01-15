# Disassemble
#
# Track opcode decode on aarch64:
# $ sudo bpftrace -e 'uprobe:/usr/bin/gdb:aarch64_opcode_decode {printf("%s\n", comm);}'
#
disassemble main
disassemble hello
disassemble /s hello,hello+20
disassemble /s hello,hello+0x20
disassemble /s 'hello','hello'+20
quit
