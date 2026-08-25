#!/bin/bash
set -e

sudo bootctl status || { if test $? != 1; then exit 1; fi }
