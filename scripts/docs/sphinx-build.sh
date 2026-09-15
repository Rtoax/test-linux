#!/bin/bash
# Work under Documentation directory
set -ex

readonly MYDIR=$(dirname $(realpath $0))
readonly DOCDIR=$(realpath ${MYDIR}/../../Documentation/)

pushd ${DOCDIR}
case ${1} in
pdfdocs)
	sphinx-build -M latexpdf . buildpdf
	;;
htmldocs | "")
	sphinx-build -M html . build
	;;
esac
popd
