target-prog-y := info.sh
target-prog-y += compile.sh compile.sh.1
target-prog-y += version.sh version.sh.1 version.sh.2 version.sh.3 version.sh.4

PROG_ARGS_compile.sh.1 := --help
PROG_ARGS_version.sh.1 := --major
PROG_ARGS_version.sh.2 := --patchlevel
PROG_ARGS_version.sh.3 := --sublevel
PROG_ARGS_version.sh.4 := --code
