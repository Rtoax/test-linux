#!/bin/bash
set -e

llc -march=bpf -mattr=help |& grep dwarfris
