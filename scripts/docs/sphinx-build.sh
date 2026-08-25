#!/bin/bash
# Work under Documentation directory
set -ex

readonly MYDIR=$(dirname $(realpath $0))
readonly DOCDIR=$(realpath ${MYDIR}/../../Documentation/)

pushd ${DOCDIR}
sphinx-build -M html . build
popd
