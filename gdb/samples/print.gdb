# print /fmt <expr>
# -----------------------------------
#	expr	任何合法的表达式
#	fmt	格式字符
#		x	十六进制
#		d	十进制
#		u	无符号
#		o	八进制
#		t	二进制
#		a	十六进制打印地址
#		c	字符格式
#		f	浮点格式
set args abc
echo --- Addresses in ELF ---\n
print &data_global_i
print &rodata_global_i
print /d data_global_i
print /x main
echo --- printf ---\n
print 'printf'
echo --- printf@plt ---\n
print 'printf@plt'
break main
run
print /c argv[0]
echo --- Addresses in MEM ---\n
echo --- data_global_i address ---\n
print &data_global_i
print &rodata_global_i
echo --- printf ---\n
print 'printf'
echo --- printf@plt ---\n
print 'printf@plt'
info proc mappings
echo --- _GLOBAL_OFFSET_TABLE_ ---\n
print /x (unsigned long)_GLOBAL_OFFSET_TABLE_
continue
quit
