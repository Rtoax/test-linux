#!/bin/bash
set -e

cat a.json | jq
cat a.json | jq -r '.[].version'
