break main
run
info proc mapping
printf "GOT[0]"
print /x _GLOBAL_OFFSET_TABLE_[0]
printf "GOT[1]"
print /x _GLOBAL_OFFSET_TABLE_[1]
printf "GOT[2]: _dl_runtime_resolve()"
print /x _GLOBAL_OFFSET_TABLE_[2]
disassemble /s _GLOBAL_OFFSET_TABLE_[2]
set $i=0
while ($i < 20)
	printf "GOT[%d]", $i
	print /x _GLOBAL_OFFSET_TABLE_[$i]
	printf "GOT[%d]", $i
	print /s &_GLOBAL_OFFSET_TABLE_[$i]
	set $i++
end
printf "---- disassemble printf@plt ----\n"
disassemble 'printf@plt'
