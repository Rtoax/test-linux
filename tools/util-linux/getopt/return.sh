#!/bin/bash
set -e

# return: -- '1.1.1'
getopt --options n:h --long name --long help -- -- 1.1.1
# return: '1.1.1' --
getopt --long name --long help -- -- 1.1.1
