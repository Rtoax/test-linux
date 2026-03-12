#!/bin/bash
set -e

key=$(mktemp --dry-run auditkey-XXXXXX)
#file=$(mktemp tmpfile-XXXXXX.out)

seperator() {
	printf "\033[32m## %s ##\033[m\n" "$*"
}

if [[ $(uname -m) == x86_64 ]]; then
	syscalls="rename,unlink,unlinkat,renameat"
elif [[ $(uname -m) == aarch64 ]]; then
	syscalls="unlinkat"
else
	exit 1
fi

seperator "--------- add audit rule ---------"
sudo auditctl \
	-a always,exit \
	-F 'arch=b64' \
	-S ${syscalls} \
	-F 'auid>=1000' \
	-F 'auid!=-1' \
	-F 'dir=/home/' \
	-F key=${key}

seperator "--------- list all audit rule ---------"
sudo auditctl -l

seperator "--------- testing ---------"
touch a.txt && rm a.txt
touch a.txt && mv a.txt b.txt && rm b.txt

seperator "--------- report ---------"
sudo ausearch -i -k ${key} -ts recent

seperator "--------- clean all ---------"
sudo auditctl -D
sudo auditctl -l
