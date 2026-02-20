#!/bin/bash
# This script only display vim version, do not display other anything,
# because the git/hooks will use it.
#
# Usage: version.sh [sharepath]
#
set -e
VIM=$(which vim 2>/dev/null || :)

vim_version() {
	if [[ -z ${VIM} ]]; then
		echo >&2 "ERROR: not found VIM in your system"
		exit 0
	fi
	${VIM} --version | grep -Eo '[0-9]+\.[0-9]+' 2>/dev/null || true
}

case $1 in
sharepath)
	if [[ -d /usr/share/vim/ ]]; then
		echo /usr/share/vim/vim$(vim_version | tr -d .)/
	elif [[ -d /usr/local/share/vim/ ]]; then
		echo /usr/local/share/vim/vim$(vim_version | tr -d .)/
	fi
	;;
"")
	vim_version
	;;
*)
	exit 1
	;;
esac
