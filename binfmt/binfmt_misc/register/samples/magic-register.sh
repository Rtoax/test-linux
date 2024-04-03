#!/bin/bash

echo ":python-magic:M::\x23PYTHON::$(which python):OC" | sudo tee /proc/sys/fs/binfmt_misc/register
cat /proc/sys/fs/binfmt_misc/python-magic

