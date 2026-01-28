#!/bin/bash
set -e

name="Rong Tao"
email=rtoax@foxmail.com

gitcmd() {
	git config --global "${@}"
}

git_config()
{
	gitcmd user.name "$name"
	gitcmd user.email "$email"
	gitcmd credential.helper store
	gitcmd http.sslVerify false
	gitcmd core.editor "vim"
	gitcmd pull.rebase false # Merge by default

	# Try to fix: fatal: The remote end hung up unexpectedly
	# - Give 1GB
	gitcmd http.postBuffer 1048576000

	# Alias
	gitcmd alias.lf "log --follow"

	# Set Proxy
	#gitcmd http.proxy http://USER:PASSWORD@127.0.0.1:8080
	#gitcmd https.proxy https://USER:PASSWORD@127.0.0.1:8080
	#gitcmd --get http.proxy
	#gitcmd --get https.proxy

	# Ignore filemode
	#git config core.filemode false

	# false: Merge
	# true: rebase
	git config pull.rebase false

	gitcmd --list
	gitcmd core.compression 0
}

git_config
