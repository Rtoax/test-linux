#!/bin/bash

restart()
{
	sudo systemctl restart tftp.service
	sudo systemctl restart dhcpd.service
	sudo systemctl restart httpd.service
}

enable_now()
{
	sudo systemctl enable --now tftp.service
	sudo systemctl enable --now dhcpd.service
	sudo systemctl enable --now httpd.service
}

restart
