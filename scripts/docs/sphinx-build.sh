#!/bin/bash
set -e

sphinx-build -M html . build --fail-on-warning
