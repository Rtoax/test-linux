#!/bin/bash
set -e

. liblog.sh

error "This is an error message" || true
warning "This is a warning message"

DEBUG=1 debug "This is a debug message"
