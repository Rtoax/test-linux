#!/bin/bash
# Work under Documentation directory
set -e

sphinx-build -M html . build
