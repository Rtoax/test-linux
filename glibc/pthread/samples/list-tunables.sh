#!/bin/bash
ld.so --list-tunables 2>/dev/null | grep -i pthread || true
