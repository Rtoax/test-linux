#!/bin/bash
# refs
# 1. https://ostreedev.github.io/ostree/introduction/
set -e

repo="./repo"

# bare - default
# archive -
ostree --repo=$repo init --mode=archive
ls
mkdir tree
ls
echo Hello world >> tree/hello.txt
ostree --repo=$repo commit --branch=foo tree
ostree --repo=$repo refs
ostree --repo=$repo ls foo
ostree --repo=$repo cat foo /hello.txt
ostree --repo=$repo checkout foo tree-checkout
cat tree-checkout/hello.txt
