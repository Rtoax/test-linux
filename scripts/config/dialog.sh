#!/bin/bash
# This is test-linux dialog config main script
#
# Copyright (C) 2025 Rong Tao. All rights reserved.
#

readonly DIALOG=$(which dialog 2>/dev/null || :)
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
readonly TITLE="${PRODUCT} Configuration"
readonly BACKTITLE="${PRODUCT} Configuration with kernel $(uname -r)"

readonly MENU_Save_and_Continue='Save and Continue'

declare -a MAIN_MENU_ITEMS=(
	"${MENU_Save_and_Continue}"
	)

. ${DIALOG_ROOT}/log.sh
. ${DIALOG_ROOT}/config.sh

# When switching TTY during the installation process (switching from TTY1
# to TTY9), the printed information of TTY1 may remain on TTY9, so clean
# the screen output here to prevent the screen output from being dialogged.
clear
trap clear EXIT
# Ignore SIGINT SIGQUIT SIGTSTP. In the interactive dialog interface,
# some keyboard signals should be ignored
trap "" INT QUIT TSTP

__save_and_continue__()
{
	local ret_status

	debug "Enter ${MENU_Save_and_Continue}"

	exec 3>&1
	${DIALOG} --backtitle "${BACKTITLE}" \
		--title "${MENU_Save_and_Continue}" \
		--yesno "Save and Continue?" \
		0 0 2>&1 1>&3

	ret_status=$?
	exec 3>&-

	case ${ret_status} in
	${DIALOG_OK})
		write_configs_to_file .config
		return ${DIALOG_OK}
		;;
	${DIALOG_CANCEL})
		debug "${MENU_Save_and_Continue} terminated.";
		return ${DIALOG_CANCEL}
		;;
	esac
}

__main__()
{
	local selection ret_status

	while :; do
		exec 3>&1
		selection=$(${DIALOG} --backtitle "${BACKTITLE}" \
			--title "${TITLE}" \
			--default-item "${MENU_Save_and_Continue}" \
			--clear --cancel-label "Exit" \
			--menu "${PRODUCT} Configuration Main Window." \
			${HEIGHT} ${WIDTH} ${MENU_HIGHT} \
			"${MENU_Save_and_Continue}" '' \
			2>&1 1>&3
		)

		ret_status=$?
		exec 3>&-
		case ${ret_status} in
		${DIALOG_CANCEL} | ${DIALOG_ESC})
			debug "Program terminated"
			break
			;;
		esac

		case ${selection} in
		${MENU_Save_and_Continue})
			__save_and_continue__
			case $? in
			${DIALOG_OK}) debug "End of the main loop"; break ;;
			*) debug "back to main menu"; continue ;;
			esac
		esac
	done
}

if [[ -z ${DIALOG} ]]; then
	crit "Not found dialog command"
fi

__main__ "$@"
