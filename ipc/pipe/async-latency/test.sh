#!/bin/bash

max_pkg_size=10000
test_size_interval=128

make

for it in $(seq 1 5)
do
	# ./main [nthread] [max-pkg-size] [pkg-size-interval] [record-file-name]
	./main $it $max_pkg_size $test_size_interval record-$it-$max_pkg_size-$test_size_interval.txt
done
