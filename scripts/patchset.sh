#!/bin/bash
# Generate patch set
set -e

subject_prefix=
downer_commit=
upper_commit=

no_cover_letter=

dumpcmd=
output_dir=tmp.patch

readonly ANSI_RED="\033[31m"
readonly ANSI_GREEN="\033[32m"
readonly ANSI_YELLOW="\033[33m"
readonly ANSI_BLUE="\033[34m"
readonly ANSI_PURPLE="\033[35m"

readonly ANSI_BOLD="\033[1m"
readonly ANSI_GRAY="\033[2m"
readonly ANSI_ITALIC="\033[3m"
readonly ANSI_UL="\033[4m" # Underline
readonly ANSI_REVERSE="\033[7m"

readonly ANSI_RESET="\033[m"

__usage__()
{
	echo -e "
${ANSI_BOLD}NAME${ANSI_RESET}
	patchset - Generate patchset

${ANSI_BOLD}SYNOPSIS${ANSI_RESET}
	patchset [options]

${ANSI_BOLD}DESCRIPTION${ANSI_RESET}
	Generate patchset to send email.

${ANSI_BOLD}ARGUMENT${ANSI_RESET}
	--subject-prefix [STR]   specify Subject prefix
	--from [COMMIT]          specify downer/older commit, see git log --oneline
	--to   [COMMIT]          specify upper/newer commit, see git log --oneline

	--no-cover-letter        no cover letter

	-o, --output [DIR]       specify output directory, default: ${output_dir}
	-d, --dumpcmd, --dry-run dump command instead execute
	-h, --help               show this help information
	-v, --verbose            show detail during running

${ANSI_BOLD}BARE GIT EXAMPLES${ANSI_RESET}
	${ANSI_GRAY}# Generate single one pretty patch${ANSI_RESET}
	$ git format-patch ${ANSI_UL}-1${ANSI_RESET} --pretty=fuller HEAD
	${ANSI_GRAY}# Generate single one patch with e-mail${ANSI_RESET}
	$ git format-patch ${ANSI_UL}-1${ANSI_RESET} HEAD --to=${ANSI_UL}rtoax@foxmail.com${ANSI_RESET} \\
				 --cc=${ANSI_UL}linux-kernel@vger.kernel.org${ANSI_RESET}
	${ANSI_GRAY}# Generate 2 patches patchset with cover letter${ANSI_RESET}
	$ git format-patch ${ANSI_UL}-2${ANSI_RESET} -s --cover-letter --thread \\
			--subject-prefix=\"${ANSI_UL}PATCH v3${ANSI_RESET}\"

${ANSI_BOLD}EXAMPLES${ANSI_RESET}
	${ANSI_GRAY}# Submit a patchset:${ANSI_RESET}
	$ patchset --from [commit1] --to [commit2]
	${ANSI_GRAY}# Then, modify 0000-cover-letter.patch${ANSI_RESET}
	$ git send-email ${dumpcmd:+--dry-run} ${output_dir}/*.patch

${ANSI_BOLD}SEE ALSO${ANSI_RESET}
	git(1), git‐format‐patch(1), git‐send‐email(1)

${ANSI_BOLD}AUTHOR${ANSI_RESET}
	Rong Tao

${ANSI_BOLD}LINKS${ANSI_RESET}
	https://kernelnewbies.org/FirstKernelPatch
" | more
	exit ${1-0}
}

__main__()
{
	TEMP=$(getopt \
		--options o:dv:h \
		--long subject-prefix: \
		--long from: \
		--long to: \
		--long no-cover-letter \
		--long output: \
		--long dumpcmd \
		--long dry-run \
		--long verbose: \
		--long help \
		-n patchset -- "$@")

	test $? != 0 && __usage__ 1

	eval set -- "$TEMP"

	while true; do
		case $1 in
		--subject-prefix)
			shift
			subject_prefix="$1"
			shift
			;;
		--from)
			shift
			downer_commit="$1"
			shift
			;;
		--to)
			shift
			if [[ -z ${downer_commit} ]]; then
				echo "ERROR: specify --from first"
				exit 1
			fi
			upper_commit="$1"
			shift
			;;
		--no-cover-letter)
			shift
			no_cover_letter=YES
			;;
		-o|--output)
			shift
			output_dir=$1
			shift
			;;
		-d|--dumpcmd|--dry-run)
			shift
			dumpcmd=YES
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
		--)
			shift
			break
			;;
		esac
	done
}

my_eval()
{
	if [[ $dumpcmd == YES ]]; then
		echo "$@"
	else
		eval "$@"
	fi
}

# Submit multi-patches at one time
# ref: https://kernelnewbies.org/FirstKernelPatch
patchset()
{
	[[ -z ${downer_commit} ]] && echo "ERROR: Must specify --from" && exit 1
	[[ -z ${upper_commit} ]] && echo "ERROR: Must specify --to" && exit 1
	if [[ -e ${output_dir} ]] && [[ ! -d ${output_dir} ]]; then
		echo "ERROR: ${output_dir} exist but is not directory"
		exit 1
	fi

	local args

	if [[ ${no_cover_letter} ]]; then
		args+=( --no-cover-letter )
	else
		args+=( --cover-letter )
	fi

	my_eval git format-patch \
		--numbered \
		--thread=shallow \
		${args[@]} \
		${subject_prefix:+--subject-prefix="'${subject_prefix}'"} \
		${downer_commit}^..${upper_commit} \
		-o ${output_dir}

	echo "
	1. modify 0000-cover-letter.patch
	2. check patches (scripts/checkpatch.pl if linux)
	3. git send-email ${dumpcmd:+--dry-run} [--to|--cc|--to-cmd=] ${output_dir}/*.patch
	"
}

__main__ "$@"
patchset
