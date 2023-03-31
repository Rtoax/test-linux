#!/bin/bash

# Disassemble and annotate instructions with percentages (needs some debuginfo):
perf annotate --stdio

# with symbol
perf annotate --stdio --symbol [function name]

