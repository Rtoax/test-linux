#!/bin/bash
# This is test-linux dialog config main script
#
# Copyright (C) 2025 Rong Tao. All rights reserved.
#

readonly DIALOG=dialog
readonly DIALOG_ROOT=$(dirname `realpath $0`)
readonly HEIGHT=$(( $(stty size | awk '{print $1}') - 10 ))
readonly MENU_HIGHT=${HEIGHT}
readonly WIDTH=$(( $(stty size | awk '{print $2}') - 10 ))

: ${DIALOG_OK=0}
: ${DIALOG_CANCEL=1}
: ${DIALOG_HELP=2}
: ${DIALOG_EXTRA=3}
: ${DIALOG_ITEM_HELP=4}
: ${DIALOG_ESC=255}

readonly PRODUCT="Test Linux"
readonly BACKTITLE="${PRODUCT} Configuration"

readonly MENU_Save_and_Continue='Save and Continue'

declare -a MAIN_MENU_ITEMS=(
	"${MENU_Save_and_Continue}"
	)

# When switching TTY during the installation process (switching from TTY1
# to TTY9), the printed information of TTY1 may remain on TTY9, so clean
# the screen output here to prevent the screen output from being dialogged.
clear
trap clear EXIT
# Ignore SIGINT SIGQUIT SIGTSTP. In the interactive dialog interface,
# some keyboard signals should be ignored
trap "" INT QUIT TSTP

mylog() {
	local prio=$1 # crit, error, warning, info, debug
	shift
	logger -t "test-linux[$$]" -p ${prio} -- "$@"
}

debug() {
	mylog debug "$@"
}

error() {
	mylog error "$@"
}

__save_and_continue__()
{
	local ret_status

	debug "Enter ${MENU_Save_and_Continue}"

	exec 3>&1
	${DIALOG} --backtitle "${BACKTITLE}" \
		--title "${MENU_Save_and_Continue}" \
		--yesno \
"Save and Continue? \n" \
		${HEIGHT} ${WIDTH} 2>&1 1>&3

	ret_status=$?
	exec 3>&-

	case ${ret_status} in
	${DIALOG_OK})
		return 0
		;;
	${DIALOG_CANCEL})
		debug "${MENU_Save_and_Continue} terminated."
		return 1
		;;
	esac
}

__main__()
{
	local selection ret_status

	while :; do
		exec 3>&1
		selection=$(${DIALOG} --backtitle "${BACKTITLE}" \
			--title "Main Menu" \
			--default-item "${MENU_Save_and_Continue}" \
			--clear --cancel-label "Exit" \
			--menu "${PRODUCT} Main Menu" \
			${HEIGHT} ${WIDTH} ${MENU_HIGHT} \
			"${MENU_Save_and_Continue}" '' \
			2>&1 1>&3
		)

		ret_status=$?
		exec 3>&-
		case ${ret_status} in
		${DIALOG_CANCEL} | ${DIALOG_ESC})
			echo >&2 -e "Program terminated"
			break
			;;
		esac

		case ${selection} in
		${MENU_Save_and_Continue})
			__save_and_continue__
			case $? in
			0)
				debug "End of the main loop"
				break
				;;
			*)
				debug "back to main menu"
				continue
				;;
			esac
			;;
		esac
	done
}

__main__ "$@"
