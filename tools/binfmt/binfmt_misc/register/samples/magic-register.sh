#!/bin/bash
set -e

register() {
	echo ":python-magic:M::\x23PYTHON::$(which python):OC" | sudo tee /proc/sys/fs/binfmt_misc/register
	cat /proc/sys/fs/binfmt_misc/python-magic
}

unregister() {
	echo '-1' | sudo tee /proc/sys/fs/binfmt_misc/python-magic
}

case $1 in
unregister)
	unregister
	;;
*)
	register
	;;
esac
