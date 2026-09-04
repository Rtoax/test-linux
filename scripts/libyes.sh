#!/bin/bash
# YES helpers
#

readonly LIBYES_ROOT=$(dirname $(readlink -f ${BASH_SOURCE[0]}))

. ${LIBYES_ROOT}/liblog.sh

# If yes echo "YES", if no echo "NO", otherwise, infinite loop.
# $1: Hint message
yes_or_no()
{
	local answer
	local hint="${@}"

	[[ -z ${hint} ]] && Hint="Are you sure? [Y/n]"

	while read -p "${@} " answer
	do
		case $answer in
		[Yy]|[Yy][Ee]|[Yy][Ee][Ss])
			echo YES
			return 0
			;;
		[Nn]|[Nn][Oo])
			echo NO
			return 0
			;;
		*)
			warning "Unknown '$answer'"
			continue
			;;
		esac
	done
}
