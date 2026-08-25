#!/bin/bash
set -e
git describe --match "v[0-9]*" --abbrev=7 HEAD 2>/dev/null
