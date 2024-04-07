#!/bin/bash
ld -v
BINUTILS_VERSION_MAJOR=$(ld -v | grep -o [0-9].[0-9]\. | tr '.' ' ' | awk '{print $1}')
BINUTILS_VERSION_MINOR=$(ld -v | grep -o [0-9].[0-9]\. | tr '.' ' ' | awk '{print $2}')
echo "Binutils version ${BINUTILS_VERSION_MAJOR}.${BINUTILS_VERSION_MINOR}"
[[ -e /usr/bin/rpm ]] && rpm -q binutils
[[ -e /usr/bin/dpkg ]] && dpkg -l binutils
