#!/bin/bash
set -e
readonly VERDIR=$(dirname $(realpath $0))
${VERDIR}/version.sh -n bcc -V -- ${@}
