	global start_of_code
	global end_of_code
section .data
start_of_code:
	incbin ".output/load-payload01-program.asm.o"
end_of_code:
