set $PROT_READ = 0x1
set $PROT_WRITE = 0x2
set $PROT_EXEC = 0x4
set $MAP_SHARED = 0x01
set $MAP_PRIVATE = 0x02
set $O_RDONLY = 00
set $O_WRONLY = 01
set $O_RDWR = 02
set $O_CREAT = 0100
set $sizeof_stat = 144
break main
run
set $fd = (int)open($file, $O_RDWR)
set $statbuf = (void *)malloc($sizeof_stat)
set $ret = (int)fstat($fd, $statbuf)
set $size = *(long *)($statbuf+48)
call (void)free($statbuf)
set $addr = (void *)mmap(0, $size, $PROT_READ | $PROT_WRITE, $MAP_SHARED, $fd, 0)
info proc mapping
call (void)munmap($addr, $size)
call (void)close($fd)
info proc mapping
continue
quit
