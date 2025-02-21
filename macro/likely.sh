#!/bin/bash
set -e

. ./utils.sh

make likely

objdump_func likely reta
objdump_func likely reta_likely
