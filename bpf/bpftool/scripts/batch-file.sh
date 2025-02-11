#!/bin/bash
set -ex

cat>batch_example.txt<<-EOF
feature list_builtins prog_types
feature list_builtins map_types
EOF

sudo bpftool batch file batch_example.txt
