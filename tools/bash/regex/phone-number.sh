#!/bin/bash
# script to filter out bad phone numbers
echo $1 | gawk --re-interval '/^\(?[2-9][0-9]{2}\)?(| |-|\[0-9]{3}( |-|\.)[0-9]{4}/{print $0}'
