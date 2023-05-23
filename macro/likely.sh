#!/bin/bash

. ./utils.sh

make

objdump_func likely reta
objdump_func likely reta_likely
