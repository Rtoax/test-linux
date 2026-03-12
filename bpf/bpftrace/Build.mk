subdir-y := samples
subdir-y += scripts
target-prog-y := version.sh version.sh.1 version.sh.2 version.sh.3

PROG_ARGS_version.sh.1 := --major
PROG_ARGS_version.sh.2 := --minor
PROG_ARGS_version.sh.3 := --patchlevel
