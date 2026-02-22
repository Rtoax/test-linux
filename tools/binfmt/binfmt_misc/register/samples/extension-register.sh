#!/bin/bash

echo ":python-extension:E::py::$(which python):OC" | sudo tee /proc/sys/fs/binfmt_misc/register
cat /proc/sys/fs/binfmt_misc/python-extension

