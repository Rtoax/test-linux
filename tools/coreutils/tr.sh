#!/bin/bash
set -ex

cat /etc/os-release | tr '[:upper:]' '[:lower:]'
cat /etc/os-release | tr '[:lower:]' '[:upper:]'
