#!/bin/bash

SRC=samples/main.c

echo "------------- GNU style -------------"
indent -st ${SRC}

echo "------------- Linux style -------------"
indent --linux-style -st ${SRC}
