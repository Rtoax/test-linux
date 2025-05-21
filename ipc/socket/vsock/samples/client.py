#!/bin/env python
# Client running in the guest
import socket

sock = socket.socket(socket.AF_VSOCK, socket.SOCK_STREAM)
sock.connect((socket.VMADDR_CID_HOST, 6789))
sock.send(b'Hello, world')
