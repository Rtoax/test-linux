#!/bin/bash
make global-var
gdb -q ./global-var -x global-var.gdb
