#!/bin/bash

dd if=/dev/random of=a.bin bs=1M count=10

md5_orig=$(md5sum a.bin | awk '{print $1}')

rm -rf a.bin.out_*
split --bytes=1M a.bin a.bin.out_
cat a.bin.out_* > a.bin.rebuild

md5_rebuild=$(md5sum a.bin.rebuild | awk '{print $1}')

if [[ ${md5_orig} != ${md5_rebuild} ]]; then
	echo "ERROR: Split and Rebuild failed, md5 not even."
else
	echo "Success!!"
fi
