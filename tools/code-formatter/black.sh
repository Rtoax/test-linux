#!/bin/bash

SRC=samples/main.py

echo "----------- yapf -----------"
black --diff ${SRC}
