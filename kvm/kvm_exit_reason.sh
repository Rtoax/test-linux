#!/bin/bash
set -e

ABSDIR=$(dirname $(realpath $0))
echo $ABSDIR

case $(uname -m) in
x86_64)
	sudo $ABSDIR/exit_reason-x86.bt
	;;
aarch64)
	sudo $ABSDIR/exit_reason-aarch64.bt
	;;
esac
