#!/bin/bash

# command not found
pre_call || {
	echo 'Failed call pre_call()'
	exit 0
}

pre_call() {
	echo "Hello"
}
