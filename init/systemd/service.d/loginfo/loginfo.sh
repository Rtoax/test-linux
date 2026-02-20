#!/bin/bash
# Logger Useful Information

log_info()
{
	logger -t "testlinux[$$]" -p "notice" -- "$@"
}

log_info "$(lsblk -f)"
log_info "$(ls -l /dev/disk/by-label/)"
