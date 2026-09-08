#!/bin/bash
# 创建文件夹，文件

# 创建文件
test_create_file()
{
	mkdir -p ./test.out
	cd ./test.out

	i=0
	while (( i < 100000 )) ; do
	  if test -e ./$i; then
		# d_alloc() here
		echo $i > ./$i
	  fi
	  ((i++))
	done

	cd ..

	rm -rf ./test.out
}

# 创建文件夹
test_create_dir()
{
	mkdir -p ./test.out
	cd ./test.out

	i=0
	while (( i < 100000 )) ; do
	  if test -e ./$i; then
		# d_alloc() here
		mkdir $i
	  fi
	  ((i++))
	done

	cd ..

	rm -rf ./test.out
}

# 生成 negative dentry
test_create_neg_dentry
{
	while :;
	do
		cd `mktemp -u /tmp/rongXXX` 2>/dev/null
	done
}
