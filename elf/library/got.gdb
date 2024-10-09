break main
run
info proc mapping
set $i=0
while ($i < 40)
	printf "GOT[%d]", $i
	print /s &_GLOBAL_OFFSET_TABLE_[$i]
	set $i++
end
quit
