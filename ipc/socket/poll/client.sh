#!/bin/bash

oneshot() {
	nc -vz 127.0.0.1 8888
}
echo_client() {
	nc 127.0.0.1 8888
}

echo_client
