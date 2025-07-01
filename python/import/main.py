#!/bin/env python
import os
import sys
from log import log_error
from libs.hello import hello1
PATH = os.path.dirname(sys.argv[0]) + "/libs"
sys.path.append(PATH)
from fuck import fuck1

print(PATH)
log_error("this is a error log")
hello1("World")
fuck1("You")
