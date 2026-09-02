#!/bin/bash
set -ex

timeout 0.01 ls
timeout --signal SIGINT 0.1 sleep 0.01
