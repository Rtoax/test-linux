#!/bin/bash
# Work under Documentation directory
set -ex

readonly MYDIR=$(dirname $(realpath $0))
readonly DOCDIR=$(realpath ${MYDIR}/../../Documentation/)

buildtype=${1}
if [[ -z ${buildtype} ]]; then
	buildtype=htmldocs
fi

pushd ${DOCDIR}
case ${buildtype} in
pdfdocs)
	sphinx-build -M latexpdf . buildpdf
	;;
htmldocs)
	sphinx-build -M html . build
	;;
*)
	echo >&2 "ERROR: unknown or not specify build type"
	exit 1
	;;
esac

echo "Build '${buildtype}' on $(date '+%Y/%m/%d %H:%M:%S')" | tee .buildtimestamp.${buildtype}.txt
popd
