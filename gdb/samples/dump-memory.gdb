break main
run
set $start = &main
set $end = $start + 32
dump memory main.bin $start $end
continue
