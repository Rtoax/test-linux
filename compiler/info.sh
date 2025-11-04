#!/bin/bash
set -e

CC=$1
[[ -z ${CC} ]] && CC=gcc

readonly LD=ld
readonly MINIMAL_C_PROG="int main(void) { return 0; }"

# Display header search paths
echo "${MINIMAL_C_PROG}" | ${CC} -x c -E -Wp,-v - -o /dev/null
echo "${MINIMAL_C_PROG}" | ${CC} -x c++ -E -Wp,-v - -o /dev/null

${CC} -print-search-dirs

${LD} --verbose | grep SEARCH_DIR

${CC} -print-file-name=crtbegin.o
${CC} -print-file-name=crtend.o
${CC} -print-file-name=crt1.o
