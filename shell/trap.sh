#!/bin/bash

exit_handler() {
	local ret=$?
	if [[ $ret != 0 ]]; then
		echo "Some thing wrong."
		exit $ret
	fi
	echo "Normal exit."
}

trap exit_handler EXIT
