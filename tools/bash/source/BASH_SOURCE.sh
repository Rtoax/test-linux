#!/bin/bash
set -x

echo BASH_SOURCE=${BASH_SOURCE[@]}
echo ROOT=$(dirname $(readlink -f ${BASH_SOURCE[0]}))
