#!/bin/bash
# req: request
set -e

# -newkey rsa:1024: 1024-bit RSA certificate
openssl req -newkey rsa:1024 -out req1.pem -keyout sslclientkey.pem -nodes \
	-subj "/CN=Rong Tao/"

# -new: generate new
# -keyout: save the private key as MOK.priv
# -outform DER: DER format (UEFI/SecureBoot must be DER)
# -out MOK.der: public certificate as MOK.der
# -nodes: without encrypting the private key
# -days 36500: the certificate validity to 100 years
# -subj: set the certificate common name
openssl req -new -x509 -newkey rsa:2048 -keyout MOK.priv -outform DER \
	-out MOK.der -nodes -days 36500 -subj "/CN=Custom Kernel Sign/"
