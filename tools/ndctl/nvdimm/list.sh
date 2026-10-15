#!/bin/bash
set -e

sudo ndctl list --dimms | jq -r '.[].dev'
