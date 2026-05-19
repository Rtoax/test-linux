#!/bin/bash
set -e

MISC=/proc/sys/fs/binfmt_misc/
NAME=python-extension

register() {
	echo ":${NAME}:E::py::$(which python):OC" | sudo tee ${MISC}/register
	cat ${MISC}/${NAME}
}

unregister() {
	echo '-1' | sudo tee ${MISC}/${NAME}
}

case $1 in
unregister)
	unregister
	;;
*)
	register
	;;
esac
