#!/bin/bash

set -e

key=$(mktemp --dry-run key-XXXXXX)

start_audit_file() {
	local file=$1
	# Listen file r=read,w=write,x=execute,a=attribute
	# and create key
	sudo auditctl -w ${file} -p rwxa -k ${key}
	# List audit rule
	sudo auditctl -l
}

report_audit() {
	# Search by key
	sudo ausearch -i -k ${key} -ts recent
}

stop_audit_file() {
	local file=$1
	# Remove audit file
	sudo auditctl -W ${file} -p rwxa -k ${key}
	sudo auditctl -l
}

clean_all_rule() {
	sudo auditctl -D
}


start_audit_file /etc/hostname

# Access /etc/hostname
cat /etc/hostname

report_audit
sleep 1
stop_audit_file /etc/hostname
