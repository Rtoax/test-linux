build:
	@echo "Compile..."
	@gcc server.c common.c -o trigger-master -lm
	@gcc client.c common.c -o trigger-slave -lm
	@echo "Compile done"
install:
	@echo "Installing..."
	@sudo cp trigger-master trigger-slave /usr/bin/
	@sudo cp trigger.service /usr/lib/systemd/system/
	@sudo systemctl start trigger.service
	@sudo systemctl enable trigger.service
	@echo "Install done."
uninstall:
	@echo "Cleaning..."
	@sudo rm -f /usr/bin/trigger-master /usr/bin/trigger-slave
	@sudo rm -f /usr/lib/systemd/system/trigger.service
	@sudo systemctl stop trigger.service
	@sudo systemctl disable trigger.service
	@sudo systemctl daemon-reload
	@echo "Clean done"
clean:
	@echo "Cleaning..."
	@rm -f *~ trigger-master trigger-slave
	@echo "Clean done"
