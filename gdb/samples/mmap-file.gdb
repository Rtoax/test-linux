break main
run
set $fd = (int)open($file, 666, 0xf)
set $size = 4096
set $addr = (void *)mmap(0, $size, 3, 1, $fd, 0)
info proc mapping
call (void)munmap($addr, $size)
call (void)close($fd)
info proc mapping
continue
quit
