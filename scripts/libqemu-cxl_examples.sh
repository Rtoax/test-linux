#!/bin/bash
set -e

. libqemu-cxl.sh

cxl_debug=on

handle_cxl_arg pxb=pxb.1
config_cxl

echo "cxl_qargs=${cxl_qargs[@]}"
echo "cxl_qmachine=${cxl_qmachine[@]}"
echo "cxl_kcmds=${cxl_kcmds[@]}"
