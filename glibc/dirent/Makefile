TARGETS :=
TARGETS += opendir
TARGETS += readdir
TARGETS += telldir
TARGETS += seekdir
TARGETS += rewinddir
TARGETS += scandir
TARGETS += fdopendir
# Demos
TARGETS += listdir
TARGETS += remove_dir

CC := gcc

CFLAGS := -Werror -Wall

TARGETS_EXTRA := generate-dir
TARGETS_CLEAN := remove-dir

include ../../template/main.mk

generate-dir:
	@mkdir -p a.dir/a/b/c/d/e
	@touch a.dir/{a,b,c,d,e}.txt

remove-dir:
	@rm -rf a.dir/

opendir: opendir.o
readdir: readdir.o
telldir: telldir.o
seekdir: seekdir.o
rewinddir: rewinddir.o
scandir: scandir.o
fdopendir: fdopendir.o
listdir: listdir.o
remove_dir: remove_dir.o
