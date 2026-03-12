post0:
	$(call log_tgt,TEST,$(@))
	$(Q)timeout 1 $(MPIRUN) -n 2 ./MPI_Init
	$(Q)timeout 1 $(MPIRUN) -n 2 ./MPI_Send
	$(Q)timeout 1 $(MPIRUN) -n 10 ./MPI_Send-2
