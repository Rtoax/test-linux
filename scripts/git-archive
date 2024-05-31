#!/bin/bash

version=$(git describe --abbrev=6 --dirty --tags 2>/dev/null)

git archive --format tar.gz --output test-linux-${version}.tar.gz main
