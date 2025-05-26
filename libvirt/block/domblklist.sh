#!/bin/bash
set -e

name=almalinux9

sudo virsh domblklist ${name}
