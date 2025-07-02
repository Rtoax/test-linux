echo --- Addresses in ELF ---\n
print &data_global_i
print &rodata_global_i
print &bss_global_i
print hello
print static_hello
break main
run
echo --- Addresses in MEM ---\n
print &data_global_i
print &rodata_global_i
print &bss_global_i
print hello
print static_hello
info proc mappings
continue
quit
