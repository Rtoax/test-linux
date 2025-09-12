#!/bin/bash

name="Rong Tao"
email=rtoax@foxmail.com

git_config()
{
	git config --global user.name "$name"
	git config --global user.email "$email"
	git config --global credential.helper store
	git config --global http.sslVerify false
	git config --global core.editor "vim"
	git config --global pull.rebase false # Merge by default

	# Try to fix: fatal: The remote end hung up unexpectedly
	# - Give 1GB
	git config --global http.postBuffer 1048576000

	git_alias() {
		git config --global alias.lf "log --follow"
	}
	git_alias

	# Set Proxy
	#git config --global http.proxy http://USER:PASSWORD@127.0.0.1:8080
	#git config --global https.proxy https://USER:PASSWORD@127.0.0.1:8080
	#git config --global --get http.proxy
	#git config --global --get https.proxy

	# Ignore filemode
	#git config core.filemode false

	# false: Merge
	# true: rebase
	git config pull.rebase false

	git config --global --list
	git config --global core.compression 0
}

git_config
