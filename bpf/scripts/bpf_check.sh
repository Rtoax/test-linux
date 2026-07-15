#!/bin/bash
set -e

sudo trace-cmd record -g bpf_check -p function_graph
#sudo trace-cmd report
