#!/bin/bash
set -e

exec 3>&1
exec > >( sed 's/^/PREFIX( /g' | sed 's/$/ )SUFFIX/g')

echo 'Hello'
exec 1>&3

echo 'World'

exec 3>&1
exec > >( sed 's/^/I Love /g' | sed 's/$/!!!/g')
echo "Rong Tao"
echo "Rong Tao 2" >&2
exec 1>&3

echo "Xue Yuehua"
