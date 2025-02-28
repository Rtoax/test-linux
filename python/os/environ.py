#!/bin/env python
import os

os.environ['MY_NAME'] = 'Rong Tao'

env_vars = os.environ

for var, value in env_vars.items():
    print(f'{var}: {value}')
