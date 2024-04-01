#!/bin/bash

echo '-1' | sudo tee /proc/sys/fs/binfmt_misc/python-extension

