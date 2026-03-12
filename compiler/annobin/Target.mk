%.annocheck.log: %
	${Q}${ANNOCHECK} ${^} | tee ${@}
