#!/bin/bash
set -e

readonly MYDIR=$(dirname $(realpath $0))
readonly DOCDIR=$(realpath ${MYDIR}/../../Documentation/)

# http://10.253.12.71/public/test-linux/build/html/index.html
# http://10.253.12.72/public/test-linux/build/html/index.html
readonly REMOTES=(
	10.253.12.71:/data2/public/test-linux
	10.253.12.72:/16t/public/test-linux
)

pushd ${DOCDIR}

make_tl build || true

for remote in ${REMOTES[@]}; do
	timeout 10 rsync -av --delete build ${remote}
done
popd
