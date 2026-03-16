#!/bin/bash

. ../scripts/make_tl.sh

make_tl clean
make_tl NOPIE=1
