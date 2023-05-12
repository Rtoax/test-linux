#!/bin/bash

gcc hello.c -g -o hello
dwarfdump hello | more
