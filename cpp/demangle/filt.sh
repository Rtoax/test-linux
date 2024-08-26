#!/bin/bash

llvm-cxxfilt _Z3foov _Z3bari not_mangled
c++filt _Z3foov _Z3bari not_mangled
