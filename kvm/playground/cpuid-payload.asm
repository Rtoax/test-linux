	global start_of_code
	global end_of_code
section .data
start_of_code:
	incbin "cpuid-program.bin"
end_of_code:

