#!/bin/env python

import os

def get_pro_environ(pid):
    with open(f'/proc/{pid}/environ', 'r')as f:
        data = f.read()
        data.strip('\x00')

    arrs = data.split('\x00')
    environ = {}

    for item in arrs:
        if not item:
            continue

        lst = item.split('=')
        environ[lst[0]] = lst[1]

    return environ

envs = get_pro_environ(os.getpid())

if envs["SHELL"]:
    print("SHELL = %s" % envs["SHELL"])

try:
    if envs["NOT_EXIST___"]:
        print("NOT_EXIST___ = %s" % envs["NOT_EXIST___"])
except:
    print("NOT_EXIST___ is not exist")
