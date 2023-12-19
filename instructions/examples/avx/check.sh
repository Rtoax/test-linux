#!/bin/bash

features=(avx avx2 avx512f)

../sh/cpu_feature_check ${features[@]}
