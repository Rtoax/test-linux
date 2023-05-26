#!/bin/bash

features=(sse sse2 ssse3 sse4_1 sse4_2)

../sh/cpu_feature_check ${features[@]}
