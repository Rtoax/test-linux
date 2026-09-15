#!/bin/bash
set -e

exec > >( sed 's/^/PREFIX( /g' | sed 's/$/ )SUFFIX/g')

echo 'Hello'
echo 'World'
