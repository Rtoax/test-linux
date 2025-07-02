source mman.gdb
source fcntl.gdb
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
