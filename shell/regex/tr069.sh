#!/bin/bash

cat oid.txt | egrep "^Device\\.[a-zA-Z]\\w+\\.(([a-zA-Z]\\w+|\\{[0-9a-z]\\})\\.)*[a-zA-Z0-9]\\w+"
