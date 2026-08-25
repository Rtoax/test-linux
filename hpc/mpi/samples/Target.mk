tmout = timeout --signal KILL 1 --preserve-status

post0:
	@$(call log_tgt,TEST,$(@))
	$(Q)${tmout} $(MPIRUN) -n 2 ./MPI_Init || true
	$(Q)${tmout} $(MPIRUN) -n 2 ./MPI_Send || true
	$(Q)${tmout} $(MPIRUN) -n 10 ./MPI_Send-2 || true
	@$(call log_tgt,TEST DONE,$(@))
