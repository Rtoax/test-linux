#!/bin/bash
set -

iostat
# -d: Display the device utilization report.
# -k: Display statistics in kibibytes per second.
iostat -d -k
