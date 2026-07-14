post0:
	@$(call log_tgt,TEST,$(@))
	$(Q)sudo chrt -r 10 ./sched_rr_get_interval
	$(Q)sudo chrt -f 10 ./sched_rr_get_interval
