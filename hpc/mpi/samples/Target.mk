post0:
	$(call log_tgt,TEST,$(@))
	$(Q)timeout 1 $(MPIRUN) -n 2 ./MPI_Init || true
	$(Q)timeout 1 $(MPIRUN) -n 2 ./MPI_Send || true
	$(Q)timeout 1 $(MPIRUN) -n 10 ./MPI_Send-2 || true
	$(call log_tgt,TEST DONE,$(@))
