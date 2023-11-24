#!/bin/bash

file=test.txt

inotifywait -m --timefmt '%H:%M' --format '%T %w %e %f' ${file}
