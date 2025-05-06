SERVICE_EXEC=dialog-hello.sh
SERVICE_NAME=simple-window-dialog.service


install: uninstall
	sudo ln -s $(shell pwd)/${SERVICE_EXEC} /usr/bin/
	sudo ln -s $(shell pwd)/${SERVICE_NAME} /usr/lib/systemd/system/
	sudo ln -sf $(shell pwd)/${SERVICE_NAME} /usr/lib/systemd/system/default.target.wants/${SERVICE_NAME}

start:
	sudo systemctl daemon-reload
	sudo systemctl start ${SERVICE_NAME}
	sudo systemctl status ${SERVICE_NAME}

uninstall:
	sudo rm -f /usr/bin/${SERVICE_EXEC} \
		/usr/lib/systemd/system/${SERVICE_NAME} \
		/usr/lib/systemd/system/default.target.wants/${SERVICE_NAME}

