#!/bin/bash
set -e

topdir=$(git rev-parse --show-toplevel 2>/dev/null || :)
version=$(git describe --abbrev=6 --dirty --tags 2>/dev/null || :)

path=$PWD
name=test-linux-${version}

pushd ${topdir}
git archive --format tar.gz --prefix=${name}/ --output ${path}/${name}.tar.gz main
popd
