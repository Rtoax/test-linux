#!/bin/bash
# Copyright (C) 2023-2026 Rong Tao.

ps_info()
{
	ps -A -o stat,ppid,pid,lstart,comm
}

ps_zombie()
{
	ps_info | grep -e '^[Zz]'
}

ps_D()
{
	ps_info | grep ^D
}

ps_sleep()
{
	ps_info | grep ^S
}

ps_mem_rss()
{
	local pid=$$

	# -O rss: show rss columns
	ps -O rss ${pid}
}

ps_sleep
