#!/bin/bash

root_dir=a.out

if [[ ! -d ${root_dir} ]]; then
	echo "ERROR: ${root_dir} is not exist."
	mkdir ${root_dir}
	exit 1
fi

recursive_touch() {
	local root=$1
	local files=$(ls $root)
	pushd $root
	touch readme
	ln -s readme README.md
	touch $(basename $root).txt
	for f in ${files[@]}
	do
		if [[ -d $f ]]; then
			recursive_touch $f
		fi
	done
	popd
}

mkdir -p ${root_dir}/a/b/c/d/e/f/g/h/i/j/k
recursive_touch ${root_dir}
tree ${root_dir}
rm -rf ${root_dir}
