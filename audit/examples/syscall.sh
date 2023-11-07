#!/bin/bash
set -e

key=$(mktemp --dry-run auditkey-XXXXXX)
#file=$(mktemp tmpfile-XXXXXX.out)

seperator() {
	printf "\033[32m## %s ##\033[m\n" "$*"
}

seperator "--------- add audit rule ---------"
sudo auditctl \
	-a always,exit \
	-F 'arch=b64' \
	-S rename,unlink,unlinkat,renameat \
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
