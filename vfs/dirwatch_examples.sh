#!/bin/bash

root_dir=a.out

if [[ ! -d ${root_dir} ]]; then
	echo "ERROR: ${root_dir} is not exist."
	exit 1
fi

mkdir -p ${root_dir}/a/b/c/d/e/f/g/h/i/j/k
touch ${root_dir}/{a,b,c,d,e,f,g,h,i,j,k}.txt
rm ${root_dir}/*txt
rm -rf ${root_dir}
