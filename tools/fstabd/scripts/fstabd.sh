#!/bin/bash
# fstabd - Used to reset /etc/fstabd after a failed modification of
# /etc/fstabd.
#
# 2023-11-30	Rong Tao	Create this.
#
set -e

readonly fstabd_version="v0.0.1"

current_event=
etc_fstab=/etc/fstab
fstabd_conf=/etc/fstabd.conf
backup_dir=/tmp/fstabd/
last_backup_fstab=
declare -a backup_fstabs
declare -a check_mountpoints

__usage__() {
	echo -e "
fstabd  - Monitor, verify and recover /etc/fstab

-f, --fstab  [file]    specify fstab instead of ${etc_fstab}
-d, --backupdir [dir]
                       specify backup directory, default: ${backup_dir}

-c, --config [config]  specify fstabd's configuration, default: ${fstabd_conf}

-h, --help             show this help information
-V, --version          show version information
-v, --verbose          show verbose information
"
	exit ${1-0}
}

__flog() {
	local lvl=$1
	shift
	local ansi ansi_reset
	case ${lvl} in
	error)
		ansi="\033[31m"
		ansi_reset="\033[m"
		;;
	warning)
		ansi="\033[35m"
		ansi_reset="\033[m"
		;;
	info)
		ansi="\033[34m"
		ansi_reset="\033[m"
		;;
	esac
	echo -e "${ansi}fstabd[$$][${lvl}](${current_event}) $@${ansi_reset}"
	logger -t "fstabd[$$](${current_event})" -p ${lvl} -- "$@"
}

ferror() {
	__flog error "$@"
}
fwarning() {
	__flog warning "$@"
}
finfo() {
	__flog info "$@"
}

set_conf() {
	local conf=$1
	if [[ ! -f ${conf} ]]; then
		ferror "${conf} is not exist."
		exit 1
	fi
	fstabd_conf=${conf}
}

parse_conf() {
	if [[ ! -e ${fstabd_conf} ]]; then
		fwarning "No config to load"
		return 0
	fi
	source ${fstabd_conf}

	check_mountpoints+=( ${FSTABD_MOUNTPOINTS[@]} )
	fwarning "Find mountpoints to check: ${check_mountpoints[@]}"
}

__main__() {
	TEMP=$(getopt \
		--options f:d:c:hvV \
		--long fstab: \
		--long backupdir: \
		--long config: \
		--long help \
		--long version \
		--long verbose \
		-n fstabd -- "$@")

	test $? != 0 && __usage__ 1

	eval set -- "$TEMP"

	while true; do
		case $1 in
		-f|--fstab)
			shift
			etc_fstab=$1
			shift
			;;
		-d|--backupdir)
			shift
			backup_dir=$1
			shift
			;;
		-c|--config)
			shift
			set_conf $1
			shift
			;;
		-h|--help)
			shift
			__usage__
			;;
		-v|--verbose)
			shift
			export PS4='+${BASH_SOURCE}:${LINENO}:${FUNCNAME[0]}: '
			set -x
			;;
		-V|--version)
			shift
			echo "fstabd: ${fstabd_version}"
			exit 0
			;;
		--)
			shift
			break
			;;
		esac
	done
}

backup_fstab() {
	local fstab=$1

	if [[ ! -d ${backup_dir} ]]; then
		mkdir -p ${backup_dir} || {
			ferror "Failed create directory ${backup_dir}"
			exit 1
		}
	fi
	local new=$(mktemp --dry-run ${backup_dir}/fstab-$(date +'%C%y-%m-%d_%H-%M-%S')-XXXXXX)
	if [[ -e ${fstab} ]]; then
		cp ${fstab} ${new}
		last_backup_fstab=${new}
		backup_fstabs+=( ${new} )
		finfo "Backup ${fstab} to ${new}"
	else
		ferror "${fstab} may be removed during backuping"
	fi
}

# $1 - init, recover
verify_fstab() {
	local operation=$1
	shift
	local fstab=$1
	local recover=

	failed_handler() {
		case $operation in
		init)
			fwarning "Failed verify ${fstab} in startup, exit."
			exit 1
			;;
		recover)
			fwarning "Failed verify ${fstab}, recover from ${last_backup_fstab}"
			cp ${last_backup_fstab} ${fstab}
			recover=YES
			return 0
			;;
		esac
	}

	# Exist check
	if [[ ! -e ${fstab} ]]; then
		fwarning "${fstab} is not exist."
		case $operation in
		init)
			exit 0
			;;
		recover)
			failed_handler
			[[ ${recover} ]] && return 0
			;;
		esac
	fi

	# Check mount points
	if ! findmnt --verify --fstab --tab-file ${fstab}; then
		fwarning "Findmnt verify failed in ${fstab}"
		failed_handler
		[[ ${recover} ]] && return 0
	fi

	# fstab must have '/' mountpoint
	for mp in ${check_mountpoints[@]}
	do
		local points=( $(cat ${fstab} | \
				sed 's/^[ |\t]*//g' | \
				grep -v '^#' | \
				awk '{print $2}' | \
				grep -w ${mp}
				) )
		local found

		# If mp=/boot, may get /boot /boot/efi
		found=
		for p in ${points[@]}
		do
			if [[ ${p} == ${mp} ]]; then
				found=YES
				break
			fi
		done
		if ! [[ "${found}" ]]; then
			fwarning "Not found '${mp}' mountpoint in ${fstab}"
			failed_handler
			[[ ${recover} ]] && return 0
		fi
	done

	# Check fstab file size, if 'echo >/etc/fstab', findmnt --verify return 0
	# TODO&HOWTO: select minimal bytes of fstab file.
	if (( $(stat -c %s ${fstab}) < 64 )); then
		if [[ ${operation} == init ]]; then
			fwarning "Modified ${fstab} is too small, exit."
			exit 1
		elif [[ ${operation} == recover ]]; then
			fwarning "Modified ${fstab} is too small, recover it"
			cp ${last_backup_fstab} ${fstab}
		fi
		return 0
	fi

	# If verify success, backup newer one
	if [[ -z ${recover} ]]; then
		backup_fstab ${fstab}
	fi
}

verify_fstab_init() {
	verify_fstab init $1
}

verify_fstab_recover() {
	verify_fstab recover $1
}

################################################################################
# main startup
__main__ "$@"

parse_conf

if [[ ! -w ${etc_fstab} ]]; then
	ferror "ERROR: ${etc_fstab} is not exist or no write permission"
	exit 1
fi

verify_fstab_init ${etc_fstab}

# Main
while true
do
	current_event=$(inotifywait \
			-e modify \
			-e delete \
			-e move \
			-e move_self \
			-e delete_self ${etc_fstab} | awk '{print $2}')
	finfo "Catch modify ${etc_fstab}"
	verify_fstab_recover ${etc_fstab}
done
