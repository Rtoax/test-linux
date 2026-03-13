target-prog-y := info.sh
target-prog-y += compile.sh compile.sh.1
target-prog-y += version.sh
target-prog-y += version.sh.1 version.sh.2 version.sh.3 version.sh.4
target-prog-y += version.sh.5 version.sh.6 version.sh.7 version.sh.8

PROG_ARGS_compile.sh.1 := --help
PROG_ARGS_version.sh.1 := --major
PROG_ARGS_version.sh.2 := --patchlevel
PROG_ARGS_version.sh.3 := --sublevel
PROG_ARGS_version.sh.4 := --code
PROG_ARGS_version.sh.5 := --uapimajor
PROG_ARGS_version.sh.6 := --uapipatchlevel
PROG_ARGS_version.sh.7 := --uapisublevel
PROG_ARGS_version.sh.8 := --uapicode
