#!/bin/bash
set -e

# FIXME: stuck seconds on 5.15.131?
timeout 3 sudo criu check
