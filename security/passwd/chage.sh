#!/bin/bash
set -e

# rongtao account will no longer be accessible
# $ sudo chage -E 2024-05-20 rongtao

# Set the minimum number of days between password changes to MIN_DAYS
# $ sudo chage -m 1 rongtao
#
# Set the maximum number of days during which a password is valid.
# $ sudo chage -M 1 rongtao

chage -l $(whoami)
