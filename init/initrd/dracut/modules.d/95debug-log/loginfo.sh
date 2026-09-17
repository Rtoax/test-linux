#!/bin/bash
# Logger Useful Information

log_info()
{
	logger -t "test-linux[$$]" -p "notice" -- "$@"
	echo "$@"
}

log_info "$(lsblk -f)"
log_info "$(blkid)"
log_info "$(ls -l /dev/disk/by-label/)"

