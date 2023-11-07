#!/bin/bash
# audit: 审计

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

seperator() {
	printf "\033[32m## %s ##\033[m\n" "$*"
}


seperator "audit add"
start_audit_file /etc/hostname
start_audit_file /etc/os-release

seperator "access file"
# Access /etc/hostname
cat /etc/hostname
cat /etc/os-release

seperator "report"
report_audit
sleep 1
seperator "audit stop"
stop_audit_file /etc/hostname
stop_audit_file /etc/os-release
