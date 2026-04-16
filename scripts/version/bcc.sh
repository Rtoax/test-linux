#!/bin/bash
set -e

readonly VERDIR=$(dirname $(realpath $0))
source ${VERDIR}/libversion.sh

version=$(${VERDIR}/version.sh -n bcc -V)

version_parser ${@} -- ${version}
