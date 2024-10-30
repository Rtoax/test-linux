#!/bin/bash

which dpkg 2>&1 >/dev/null && dpkg --list | grep linux-image

