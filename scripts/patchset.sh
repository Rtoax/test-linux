#!/bin/bash
# Copyright (c) 2022-2025 Rong Tao
# Generate patch set in git repo.
set -e

subject_prefix=
downer_commit=
upper_commit=

no_cover_letter=

dry_run=
output_dir=tmp.patch

declare -a abbrev_commits

readonly RED="\033[31m"
readonly GREEN="\033[32m"
readonly YELLOW="\033[33m"
readonly BLUE="\033[34m"
readonly PURPLE="\033[35m"

readonly BOLD="\033[1m"
readonly GRAY="\033[2m"
readonly ITALIC="\033[3m"
readonly UL="\033[4m" # Underline
readonly REVERSE="\033[7m"

readonly RST="\033[m"

__usage__()
{
	echo -e "
${BOLD}NAME${RST}
	patchset - Generate patchset

${BOLD}SYNOPSIS${RST}
	patchset [options] -- [commit1|commit2|...]

${BOLD}DESCRIPTION${RST}
	Generate patchset to send email.

${BOLD}ARGUMENT${RST}
	--subject-prefix [STR]   specify Subject prefix
	--from [COMMIT]          specify downer/older commit, see git log --oneline
	--to   [COMMIT]          specify upper/newer commit, see git log --oneline

	--no-cover-letter        no cover letter

	-o, --output [DIR]       specify output directory, default: ${output_dir}
	-n, --dry-run            dump command instead execute
	-h, --help               show this help information
	-v, --verbose            show detail during running

${BOLD}BARE GIT EXAMPLES${RST}
	${GRAY}# Generate single one pretty patch${RST}
	$ git format-patch ${UL}-1${RST} --pretty=fuller HEAD
	${GRAY}# Generate single one patch with e-mail${RST}
	$ git format-patch ${UL}-1${RST} HEAD --to=${UL}rtoax@foxmail.com${RST} \\
				 --cc=${UL}linux-kernel@vger.kernel.org${RST}
	${GRAY}# Generate 2 patches patchset with cover letter${RST}
	$ git format-patch ${UL}-2${RST} -s --cover-letter --thread \\
			--subject-prefix=\"${UL}PATCH v3${RST}\"

${BOLD}EXAMPLES${RST}
	${GRAY}# Submit a patchset:${RST}
	$ patchset --from [commit1] --to [commit2]
	${GRAY}# Then, modify 0000-cover-letter.patch${RST}
	${GRAY}# check patches (scripts/checkpatch.pl if linux)${RST}
	$ git send-email ${dry_run:+--dry-run} ${GRAY}[--to|--cc|--to-cmd=]${RST} ${output_dir}/*.patch

${BOLD}DEVELOPE GIT PATCHSET${RST}
	$ git rebase ${BOLD}<parent commit of modified commit>${RST} --interactive
	${GRAY}# Then, change the 'pick' in front of the commit that needs to be
	# changed to 'edit', then, save and exit;${RST}
	${GRAY}# Then, modify the code.${RST}
	$ git add ${BOLD}<files>${RST} ${GRAY}[--all]${RST}
	$ git commit --amend
	$ git rebase --continue

${BOLD}SEE ALSO${RST}
	git(1), git‐format‐patch(1), git‐send‐email(1)

${BOLD}AUTHOR${RST}
	Rong Tao

${BOLD}LINKS${RST}
	https://kernelnewbies.org/FirstKernelPatch
	https://www.kernel.org/doc/html/latest/process/submitting-patches.html
" | more
	exit ${1-0}
}

error() {
	echo -e >&2 "${RED}ERROR: ${@}${RST}"
	exit 1
}

warning() {
	echo -e >&2 "${RED}WARNING: ${@}${RST}"
}

__main__()
{
	local TEMP=$(getopt \
		--options o:nv:h \
		--long subject-prefix: \
		--long from: \
		--long to: \
		--long no-cover-letter \
		--long output: \
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
				error "specify --from first"
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
		-n|--dry-run)
			shift
			dry_run=YES
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
			abbrev_commits+=( $@ )
			break
			;;
		esac
	done
}

my_eval()
{
	if [[ $dry_run == YES ]]; then
		echo "$@"
	else
		eval "$@"
	fi
}

# Submit multi-patches at one time
# ref: https://kernelnewbies.org/FirstKernelPatch
patchset()
{
	if [[ -z ${downer_commit} ]] || [[ -z ${upper_commit} ]]; then
		error "Must specify --from and --to"
	fi
	if [[ -e ${output_dir} ]] && [[ ! -d ${output_dir} ]]; then
		error "${output_dir} exist but is not directory"
	fi

	local args

	args+=( --numbered )
	args+=( --thread=shallow )

	if [[ ${no_cover_letter} ]]; then
		args+=( --no-cover-letter )
	else
		args+=( --cover-letter )
	fi

	my_eval git format-patch \
		${args[@]} \
		${subject_prefix:+--subject-prefix="'${subject_prefix}'"} \
		${downer_commit}^..${upper_commit} \
		-o ${output_dir}
}

__main__ "$@"

# If the -- parameter is specified, a summary of the
# commit is displayed.
if [[ " ${@} " =~ " -- " ]]; then
	git_cmd="git log"
	if [[ ${#abbrev_commits[@]} -ge 1 ]]; then
		git_cmd="git show --no-patch"
	fi
	my_eval ${git_cmd} --abbrev=12 --pretty=format:\''commit %h ("%s")'\' ${abbrev_commits[@]}
else
	patchset
fi
