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
printf "GOT[3]"
print /s &_GLOBAL_OFFSET_TABLE_[3]
printf "GOT[4]"
print /x _GLOBAL_OFFSET_TABLE_[4]
printf "GOT[4]"
print /s &_GLOBAL_OFFSET_TABLE_[4]
printf "GOT[5]"
print /x _GLOBAL_OFFSET_TABLE_[5]
printf "GOT[5]"
print /s &_GLOBAL_OFFSET_TABLE_[5]
printf "GOT[6]"
print /x _GLOBAL_OFFSET_TABLE_[6]
printf "GOT[6]"
print /s &_GLOBAL_OFFSET_TABLE_[6]
printf "GOT[7]"
print /x _GLOBAL_OFFSET_TABLE_[7]
printf "GOT[7]"
print /s &_GLOBAL_OFFSET_TABLE_[7]
printf "GOT[8]"
print /x _GLOBAL_OFFSET_TABLE_[8]
printf "GOT[8]"
print /s &_GLOBAL_OFFSET_TABLE_[8]
printf "GOT[9]"
print /x _GLOBAL_OFFSET_TABLE_[9]
printf "GOT[9]"
print /s &_GLOBAL_OFFSET_TABLE_[9]
printf "GOT[10]"
print /x _GLOBAL_OFFSET_TABLE_[10]
printf "GOT[10]"
print /s &_GLOBAL_OFFSET_TABLE_[10]
printf "GOT[11]"
print /x _GLOBAL_OFFSET_TABLE_[11]
printf "GOT[11]"
print /s &_GLOBAL_OFFSET_TABLE_[11]
printf "GOT[12]"
print /x _GLOBAL_OFFSET_TABLE_[12]
printf "GOT[12]"
print /s &_GLOBAL_OFFSET_TABLE_[12]
printf "GOT[13]"
print /x _GLOBAL_OFFSET_TABLE_[13]
printf "GOT[13]"
print /s &_GLOBAL_OFFSET_TABLE_[13]
printf "GOT[14]"
print /x _GLOBAL_OFFSET_TABLE_[14]
printf "GOT[14]"
print /s &_GLOBAL_OFFSET_TABLE_[14]
printf "---- disassemble printf@plt ----\n"
disassemble 'printf@plt'
