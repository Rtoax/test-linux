post0:
	$(call log_tgt,TEST,$(@))
	$(Q)./shm-writer && ./shm-reader
	$(Q)./mmap-writer && ./mmap-reader
