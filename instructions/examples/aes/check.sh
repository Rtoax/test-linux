#!/bin/bash

features=$(lscpu | grep -o ' aes ')

../sh/cpu_fearute_check ${features[@]}
