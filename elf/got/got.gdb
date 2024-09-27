break main
run
printf "GOT[0]"
print /x _GLOBAL_OFFSET_TABLE_[0]
printf "GOT[1]"
print /x _GLOBAL_OFFSET_TABLE_[1]
printf "GOT[2]: _dl_runtime_resolve()"
print /x _GLOBAL_OFFSET_TABLE_[2]
disassemble /s _GLOBAL_OFFSET_TABLE_[2]
printf "GOT[3]"
print /x _GLOBAL_OFFSET_TABLE_[3]
disassemble 'printf@plt'
