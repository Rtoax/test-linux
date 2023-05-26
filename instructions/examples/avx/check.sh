#!/bin/bash

features=(avx avx2)

../sh/cpu_feature_check ${features[@]}
