#!/bin/bash
# git: https://github.com/soimort/translate-shell

trans -proxy 10.32.0.200:8080 'Saluton, Mondo!'
trans -proxy 10.32.0.200:8080 -brief 'Saluton, Mondo!'

# Command line mode
# trans -x 10.32.0.200:8080 -shell -brief
