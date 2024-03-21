#!/bin/bash

openssl req -newkey rsa:2048 -nodes \
	-keyout serverKey.pem \
	-x509 -days 365 -out serverCert.cer \
	-subj "/C=CN/ST=GD/L=GZ/O=abc/OU=defg/CN=hijk/emailAddress=rtoax@foxmail.com"
