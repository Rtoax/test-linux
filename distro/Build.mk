subdir-y += anaconda
subdir-y += rpm

target-prog-y += version.sh version.sh.1
target-prog-y += README.md.check.sh

PROG_ARGS_version.sh.1 := short
