#!/bin/bash
set -e
exec 2>&1 1>rw.log

fuser -av rw.log
