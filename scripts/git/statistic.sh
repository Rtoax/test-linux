#!/bin/bash
set -e

verbose=

git_repo=
git_since=
git_before=
git_author=
git_from_commit=
git_to_commit=

declare -a git_authors
declare -a git_authors_add
declare -a git_authors_del
declare -a git_authors_commits

export git_authors

debug()
{
	[[ -z ${verbose} ]] && return 0
	echo "$@" >&2
}

git_all_tags()
{
	git show-ref --tags | sed 's|refs/tags/||g'
}

git_log_format()
{
	readonly local commit=$1
	git log ${commit} --format='%at %aN'
}

git_getnumoffilesfromcommit()
{
	readonly local commit=$1
	git ls-tree -r --name-only ${commit}
}

git_log_numstat()
{
	# Format:
	# 2       2       Makefile
	# ^       ^
	# add     delete
	git log --author='Rong Tao' --pretty=tformat: --numstat HEAD^..HEAD
}

# git log --numstat is a better way.
git_code_add_and_delete_by_author_deprecated()
{
	echo "-----------------------------------------------"
	[[ ! -z ${git_repo} ]] && pushd ${git_repo}

	git log --stat \
		${git_author:+--author "$git_author"} \
		${git_since:+--since "$git_since"} \
		${git_before:+--before "$git_before"} \
		| awk '
	BEGIN {
		authorname = "NULL"
	}
	{
		if ($1 == "Author:") {
			authorname=$2" "$3" "$4" "$5;
		}
		if ($5 == "insertions(+)" || $5 == "insertions(+),") {
			author[authorname] += $4;
		}
		if ($5 == "deletions(-)") {
			author_del[authorname] += $4;
		}
		if ($7 == "deletions(-)") {
			author_del[authorname] += $6;
		}
	} END {
		for (a in author) {
			print(a, "+", author[a], ", -", author_del[a]);
		}
	}
	'

	[[ ! -z ${git_repo} ]] && popd

	return 0
}

__usage__()
{
	echo -e "
git-statistic - statistic git repo

   -r, --repo         specify git repo root directory
   -a, --author       specify Author, such as: --author=\"Rong Tao\"

   --since            stat since, such as: --since=\"Mon Jan 29 11:43:10 2024\"
   --before           stat before, such as: --before=\"Mon Jan 29 11:43:10 2024\"

   --from             specify downer/older commit, see git log --oneline
   --to               specify upper/newer commit, see git log --oneline

   -h, --help         show this help information
   -v, --verbose      show detail during running

   Wrote by Rong Tao
" | more

	exit ${1-0}
}

__main__()
{
	TEMP=$(getopt \
		--options r:a:vh \
		--long repo: \
		--long author: \
		--long since: \
		--long before: \
		--long from: \
		--long to: \
		--long verbose \
		--long help \
		-n git-statistic -- "$@")

	test $? != 0 && __usage__ 1

	eval set -- "$TEMP"

	while true; do
		case $1 in
		-r|--repo)
			shift
			git_repo="$1"
			[[ ! -d $git_repo ]] && \
				echo "ERROR: $git_repo is not directory" && \
				exit 1
			shift
			;;
		-a|--author)
			shift
			git_author="$1"
			shift
			;;
		--since)
			shift
			git_since="$1"
			shift
			;;
		--before)
			shift
			git_before="$1"
			shift
			;;
		--from)
			shift
			git_from_commit="$1"
			shift
			;;
		--to)
			shift
			if [[ -z ${git_from_commit} ]]; then
				echo "ERROR: specify --from first"
				exit 1
			fi
			git_to_commit="$1"
			shift
			;;
		-h|--help)
			shift
			__usage__
			;;
		-v|--verbose)
			shift
			set -x
			verbose=YES
			;;
		--)
			shift
			break
			;;
		esac
	done
}

get_all_authors()
{
	debug "== Get all authors"
	while read author
	do
		debug $author
		git_authors+=( "${author}" )
	done <<< $(git shortlog -sn | awk '{$1 = "";print $0}')
}

get_author_numstat()
{
	debug "== Get all authors numstat"
	for author in "${git_authors[@]}"
	do
		debug $author
		local add_sum=0
		local del_sum=0
		while read add del file
		do
			# git log command maybe return nothing
			if [[ -z "$add" ]] || [[ -z "$del" ]]; then
				continue
			fi
			# binary file don't have line num
			if [[ $add == - ]] || [[ $del == - ]]; then
				continue
			fi
			add_sum=$(( add_sum + $add ))
			del_sum=$(( del_sum + $del ))
		done <<< $(git log --author "$author" --pretty=tformat: \
			${git_since:+--since "$git_since"} \
			${git_before:+--before "$git_before"} \
			${git_from_commit:+${git_from_commit}^..${git_to_commit}} \
			--numstat)

		git_authors_add+=( $add_sum )
		git_authors_del+=( $del_sum )
	done
}

get_author_commits()
{
	debug "== Get all authors numstat"
	for author in "${git_authors[@]}"
	do
		debug $author
		local nr_commits=$(git shortlog -sn --no-merges --author "${author}" \
			${git_since:+--since "$git_since"} \
			${git_before:+--before "$git_before"} \
			${git_from_commit:+${git_from_commit}^..${git_to_commit}} \
			| awk '{print $1}')
		if [[ -z $nr_commits ]]; then
			nr_commits=0
		fi
		git_authors_commits+=( $nr_commits )
	done
	debug ${git_authors_commits[@]}
}

print_author_numstat()
{
	printf "%-20s\t%-8s\t%-16s\t%-16s\n" AUTHOR COMMITS ADD_LINES DELETE_LINES
	printf "%-20s\t%-8s\t%-16s\t%-16s\n" ---- ---- ---- ----
	for ((ia=0; ia < ${#git_authors[@]}; ia++))
	do
		local author=${git_authors[$ia]}
		local nr_commits=${git_authors_commits[$ia]}
		local n_add=${git_authors_add[$ia]}
		local n_del=${git_authors_del[$ia]}
		printf "%-20s\t%-8s\t%-16s\t%-16s\n" "$author" $nr_commits $n_add $n_del
	done
}

print_commit_of_author()
{
	echo "-----------------------------------------------"
	git shortlog -sne --all
	echo "-----------------------------------------------"
	git shortlog -sn --no-merges
}

goodbye()
{
	local ret=$?
	test $ret != 0 && echo "Running wrong" && exit $ret
}
trap "goodbye" EXIT

check_git() {
	git status >/dev/null 2>&1 || {
		echo "ERROR: This is not git repository."
		exit 1
	}
}

cmd_git_statistic()
{
	__main__ "$@"

	[[ ! -z ${git_repo} ]] && pushd ${git_repo}

	check_git

	get_all_authors
	get_author_numstat
	get_author_commits

	print_author_numstat

	print_commit_of_author

	[[ ! -z ${git_repo} ]] && popd

	return 0
}

if [[ $0 == /usr/bin/git-statistic ]] || [[ $0 == ./git-statistic.sh ]]; then
	cmd_git_statistic "$@"
fi
