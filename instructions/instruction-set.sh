#!/bin/bash
gcc -march=native -Q --help=target | grep -e '^  -march=' | awk '{print $2}'
