#!/bin/bash
# Test logger service

remove_old()
{
	test -e /usr/lib/systemd/system/logger.service && \
		sudo rm -f /usr/lib/systemd/system/logger.service
	test -e /usr/lib/systemd/system/logger.timer && \
		sudo rm -f /usr/lib/systemd/system/logger.timer
	test -e /usr/bin/loginfo.sh && \
		sudo rm -f /usr/bin/loginfo.sh
}

copy_to_system()
{
	sudo cp logger.timer /usr/lib/systemd/system/
	sudo cp logger.service /usr/lib/systemd/system/
	sudo cp loginfo.sh /usr/bin/
}

start_timer()
{
	sudo systemctl daemon-reload
	sudo systemctl start logger.timer
	sudo systemctl status logger.service
}

# /etc/systemd/system/multi-user.target.wants/logger.timer → /usr/lib/systemd/system/logger.timer
enable_timer()
{
	sudo systemctl enable logger.timer
}

disable_timer()
{
	sudo systemctl disable logger.timer
}

stop_timer()
{
	sudo systemctl stop logger.timer
}

clean_logger()
{
	stop_timer
	remove_old
}

case $1 in
copy)
	remove_old
	copy_to_system
	;;
start)
	start_timer
	;;
enable)
	enable_timer
	;;
disable)
	disable_timer
	;;
stop)
	stop_timer
	;;
remove)
	clean_logger
	;;
*)
	echo -e "
 [opt]
  copy     - copy service and timer to system
  start    - start timer
  stop     - stop timer
  enable   - enable timer
  disable  - disable timer
  remove   - remove all
"
	;;
esac

