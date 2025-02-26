#!/bin/bash

journalctl_error()
{
	journalctl -b -1 -p err
}

journalctl_tail()
{
	journalctl -n 30
}

journalctl_live()
{
	journalctl -f
}

journalctl_live_unit()
{
	journalctl -f -u containerd.service
}

journalctl_cmd()
{
	journalctl /usr/bin/bash
}

journalctl_unit()
{
	journalctl -u sshd.service
}

journalctl_since_until()
{
	journalctl -S "2023-08-08 13:00:00" -U "2023-08-08 20:00:00"
}
