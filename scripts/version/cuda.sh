#!/bin/bash
set -e
$(dirname $(realpath $0))/version.sh -n cuda -V -- ${@}
