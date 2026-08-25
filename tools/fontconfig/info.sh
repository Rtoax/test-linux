#!/bin/bash
set -e

fc-list
fc-list ':charset=2513' family
fc-list "DejaVu Sans Mono:charset=2513" family
