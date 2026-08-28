#!/bin/bash
set -e

. libqemu-cxl.sh

handle_cxl_arg debug
handle_cxl_arg pxb=pxb.1
config_cxl

echo "cxl_qargs=${cxl_qargs[@]}"
echo "cxl_qmachine=${cxl_qmachine[@]}"
echo "cxl_kcmds=${cxl_kcmds[@]}"
