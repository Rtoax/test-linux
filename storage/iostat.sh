#!/bin/bash
set -e

iostat | grep -e ^sd -e ^nvme -e ^vd

iostat -x 1
