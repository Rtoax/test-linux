#!/bin/bash

# Only testing on Ubuntu/Debian

mkdir -p dir1/
touch dir1/{f1,f2}

mkdir dir2
touch dir1/{f3,f4}

mkdir union

unionfs dir1/:dir2/ union/

ls union/
