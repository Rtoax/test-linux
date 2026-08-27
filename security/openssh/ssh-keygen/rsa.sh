#!/bin/bash
set -e
ssh-keygen -t rsa -N "" -b 1024 -f id_rsa -C "rtoax@foxmail.com"
