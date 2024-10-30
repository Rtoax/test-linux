#!/bin/bash
# Generate patch set
set -e

subject_prefix=
downer_commit=
upper_commit=

no_cover_letter=

dumpcmd=
output_dir=tmp.patch

__usage__()
{
	echo -e "
NAME
	patchset - Generate patchset

SYNOPSIS
	patchset [options]

DESCRIPTION
	Generate patchset to send email.

ARGUMENT
	--subject-prefix [STR]   specify Subject prefix
	--from [COMMIT]          specify downer/older commit, see git log --oneline
	--to   [COMMIT]          specify upper/newer commit, see git log --oneline

	--no-cover-letter        no cover letter

	-o, --output [DIR]       specify output directory, default: ${output_dir}
	-d, --dumpcmd, --dry-run dump command instead execute
	-h, --help               show this help information
	-v, --verbose            show detail during running

AUTHOR
	Rong Tao <rongtao@cestc.cn>

SEE ALSO
	git(1), git‐format‐patch(1), git‐send‐email(1)

EXAMPLES
	# Submit a patchset:
	$ patchset --from [commit1] --to [commit2]
	# Then, modify 0000-cover-letter.patch
	$ git send-email ${dry_run:+--dry-run} ${output_dir}/*.patch

LINKS
	https://kernelnewbies.org/FirstKernelPatch
"
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

	# Generate single one pretty patch:
	# $ git format-patch -1 --pretty=fuller HEAD
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
	3. git send-email ${dry_run:+--dry-run} [--to|--cc|--to-cmd=] ${output_dir}/*.patch
	"
}

__main__ "$@"
patchset
