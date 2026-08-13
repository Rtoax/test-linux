#!/bin/bash
set -e

. librun.sh

dry_run ls
DRY_RUN= dry_run ls
DRY_RUN=1 dry_run ls
