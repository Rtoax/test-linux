#!/bin/bash

sudo perf trace -e "write*" --syscalls
