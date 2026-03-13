post0:
	$(Q)LD_PRELOAD=./libmcount-nop.so ./main
	$(Q)LD_PRELOAD=./libconstructor-obj.so ./main

post-fentry:
	$(Q)LD_PRELOAD=./libmcount-nop.so ./fentry
