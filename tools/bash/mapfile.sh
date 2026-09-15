#!/bin/bash
set -e

doc_dirs=( a b c Documentation e f Documentation g )

mapfile -t doc_dirs < <(printf '%s\n' "${doc_dirs[@]}" | grep -iv 'Documentation')

echo ${doc_dirs[@]}

if [[ "${doc_dirs[*]}" != "a b c e f g" ]]; then
	exit 1
fi
