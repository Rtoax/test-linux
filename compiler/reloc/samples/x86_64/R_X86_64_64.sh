#!/bin/bash
set -ex

SYM=s7

readelf --syms --wide R_X86_64_64.o
readelf --relocs --wide R_X86_64_64.o
readelf --syms --wide R_X86_64_64
readelf --relocs --wide R_X86_64_64
