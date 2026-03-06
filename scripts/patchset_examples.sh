#!/bin/bash
set -e

./patchset.sh -v
./patchset.sh --version
./patchset.sh -V
./patchset.sh --verbose
./patchset.sh -h | cat
./patchset.sh --help | cat
./patchset.sh --from 54103fd68173 --to b0cb7b6917c0 --no-cover-letter --subject-prefix='PATCH bpf-next'
./patchset.sh --from 54103fd68173 --to b0cb7b6917c0 --no-cover-letter --pure-diff --output tmp.patch.diff

# display the commits
./patchset.sh -- HEAD 54103fd68173 b0cb7b6917c0

# display patchset commits and save-patchset at the same time
./patchset.sh --from HEAD --to HEAD -- patchset.sh

# get patch info
{
	./patchset.sh --from=1f28d343262b --to=1f28d343262b --no-cover-letter
	if [[ "$(./patchset.sh --patch patchset.patch/0001-patchset.sh-update-help-info.patch)" != "patchset.sh: update help info" ]]; then
		echo >&2 "ERROR: --patch run failed."
		exit 1
	fi
}
