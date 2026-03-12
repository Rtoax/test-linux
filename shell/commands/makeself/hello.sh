#!/bin/bash
set -e

makeself --gzip --sha256 hello hello_installer.run "Hello" ./hello/installer.sh
