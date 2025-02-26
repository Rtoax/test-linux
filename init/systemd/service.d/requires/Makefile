# Test Requires and After

install: uninstall
	sudo cp a.sh b.sh /usr/bin/
	sudo cp a.service b.service c.service /usr/lib/systemd/system/
	sudo systemctl daemon-reload
	# Disable b.service and c.service
	sudo systemctl disable --now b.service c.service || true
	sudo systemctl status a.service b.service c.service || true
	sudo systemctl enable --now a.service
	sleep 1
	sudo systemctl status a.service b.service c.service || true

uninstall:
	sudo systemctl disable --now a.service b.service c.service || true
	sudo rm -f /usr/bin/a.sh /usr/bin/b.sh \
		/usr/lib/systemd/system/a.service \
		/usr/lib/systemd/system/b.service \
		/usr/lib/systemd/system/c.service
	sudo systemctl daemon-reload

