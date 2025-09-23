#!/bin/bash
# produce: sshd[155200]: pam_systemd(sshd:session): Failed to create session: Maximum number of sessions (64) reached, refusing further sessions.
set -e

# See /etc/systemd/logind.conf SessionsMax=8192
for i in $(seq 1 8200); do
	ssh nuc11 sudo sleep 10 &
done
