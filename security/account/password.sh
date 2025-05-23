#!/bin/bash

# sudo dnf install -y libpwquality

random_pw=(
	$(pwmake 64)
	$(pwmake 128)
	$(pwmake 256)
)

echo random password: ${random_pw[@]}
