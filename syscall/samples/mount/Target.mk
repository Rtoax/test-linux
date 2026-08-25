fs.ext4:
	@$(call log_tgt,FS,$(@))
	${Q}./mkfs.sh
	${Q}mkdir -p tmp-dir
