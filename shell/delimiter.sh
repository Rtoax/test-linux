#!/bin/bash

wc -l << EOF
    This is a simple lookup program
    for good (and bad) restaurants
    in Cape Town.
EOF

more << FLAG
    rong
    *.*
    "\n"
FLAG

cat << EOF
    This is a simple lookup program
    for good (and bad) restaurants
    in Cape Town.
EOF

