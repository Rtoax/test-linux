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

target-post-y := generate-dir

generate-dir:
	@mkdir -p a.dir/a/b/c/d/e
	@touch a.dir/{a,b,c,d,e}.txt
	@./remove_dir
