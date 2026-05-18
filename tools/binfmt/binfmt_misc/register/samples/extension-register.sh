#!/bin/bash
set -e

register() {
	echo ":python-extension:E::py::$(which python):OC" | sudo tee /proc/sys/fs/binfmt_misc/register
	cat /proc/sys/fs/binfmt_misc/python-extension
}

unregister() {
	echo '-1' | sudo tee /proc/sys/fs/binfmt_misc/python-extension
}

case $1 in
unregister)
	unregister
	;;
*)
	register
	;;
esac
