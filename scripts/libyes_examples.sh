#!/bin/bash
set -e
. liblog.sh
. libyes.sh

if
	[[ $(echo y | yes_or_no) != YES ]] ||
	[[ $(echo ye | yes_or_no) != YES ]] ||
	[[ $(echo yes | yes_or_no) != YES ]] ||
	[[ $(echo Y | yes_or_no) != YES ]] ||
	[[ $(echo Ye | yes_or_no) != YES ]] ||
	[[ $(echo YE | yes_or_no) != YES ]] ||
	[[ $(echo YEs | yes_or_no) != YES ]] ||
	[[ $(echo YES | yes_or_no) != YES ]] ||
	[[ $(echo YeS | yes_or_no) != YES ]] ||
	[[ $(echo Yes | yes_or_no) != YES ]] ||
	[[ $(echo n | yes_or_no) != NO ]] ||
	[[ $(echo nO | yes_or_no) != NO ]] ||
	[[ $(echo no | yes_or_no) != NO ]] ||
	[[ $(echo NO | yes_or_no) != NO ]] ||
	[[ ! -z $(echo | yes_or_no) ]] ||
	[[ ! -z $(echo Nx | yes_or_no) ]] ||
	[[ ! -z $(echo yx | yes_or_no) ]] ||
	[[ ! -z $(echo Hello | yes_or_no) ]]
then
	error "Testing yes_or_no() failed"
fi
