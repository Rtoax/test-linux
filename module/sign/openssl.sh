#!/bin/bash

openssl req -new -nodes -utf8 -sha256 -days 36500 -batch -x509 \
	-config x509.genkey -outform PEM -out kernel_key.pem \
	-keyout kernel_key.pem
