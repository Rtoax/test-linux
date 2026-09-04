#!/bin/bash
set -e

test0() {
	getopt --options n:h --long name: --long help -- "${@}"
}

if
   [[ "$(test0 --help)" != " --help --" ]] ||
   [[ "$(test0 --name rongtao --name rongtao)" != " --name 'rongtao' --name 'rongtao' --" ]] ||
   [[ "$(test0 name1 name2)" != " -- 'name1' 'name2'" ]]
then
	exit 1
fi
