target-y :=
target-y += opendir
target-y += readdir
target-y += telldir
target-y += seekdir
target-y += rewinddir
target-y += scandir
target-y += fdopendir
# Demos
target-y += listdir
target-y += remove_dir

CC := gcc

CFLAGS :=

target-post-y := generate-dir
target-clean-y := remove-dir

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
