targets :=
targets += opendir
targets += readdir
targets += telldir
targets += seekdir
targets += rewinddir
targets += scandir
targets += fdopendir
# Demos
targets += listdir
targets += remove_dir

CC := gcc

CFLAGS :=

targets-post := generate-dir
targets-clean := remove-dir

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
