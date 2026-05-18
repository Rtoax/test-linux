#!/bin/bash
set -e

name="Rong Tao"
email=rtoax@foxmail.com

config() {
	git config --global "${@}"
}

git_config()
{
	config user.name "$name"
	config user.email "$email"
	config credential.helper store
	config http.sslVerify false
	config core.editor "vim"
	config pull.rebase false # Merge by default

	# Try to fix: fatal: The remote end hung up unexpectedly
	# - Give 1GB
	config http.postBuffer 1048576000

	# Alias
	config alias.lf "log --follow"

	# Set Proxy
	#config http.proxy http://USER:PASSWORD@127.0.0.1:8080
	#config https.proxy https://USER:PASSWORD@127.0.0.1:8080
	#config --get http.proxy
	#config --get https.proxy

	# Ignore filemode
	#git config core.filemode false

	# false: Merge
	# true: rebase
	git config pull.rebase false

	config core.compression 0

	# Support chinese with 'git status'
	config core.quotepath false

	config --list
}

git_config
