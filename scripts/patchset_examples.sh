#!/bin/bash
set -e

./patchset.sh --help | cat
./patchset.sh --from 54103fd68173 --to b0cb7b6917c0 --no-cover-letter
./patchset.sh -- HEAD 54103fd68173 b0cb7b6917c0
