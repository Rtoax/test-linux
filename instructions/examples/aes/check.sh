#!/bin/bash

features=$(lscpu | grep -o ' aes ')

../sh/cpu_feature_check ${features[@]}
