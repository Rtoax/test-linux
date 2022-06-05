
uid=$(shell id -g)

all:
	@echo "Command"
	@echo sudo make build
	@echo sudo make install
	@echo make check 
	@echo sudo make sepolicy
	@echo make rebuild
	@echo make restart
	@echo make check
	@echo make ausearch
	@echo make sealert
	@echo make verification
	@echo make clean
	@echo $(uid)
ifneq ($(uid),0)
	@echo -e "Must root" && exit 1
endif
	@echo make test for all

test:build install check sepolicy rebuild restart check ausearch sealert verification clean

build:
	gcc -o mydaemon mydaemon.c

install:
	sudo cp mydaemon /usr/local/bin/ 
	sudo cp mydaemon.service /usr/lib/systemd/system
	sudo systemctl start mydaemon
	sudo systemctl status mydaemon

check:
	ps -efZ | grep mydaemon

sepolicy:
	sudo sepolicy generate --init /usr/local/bin/mydaemon

rebuild:
	sudo ./mydaemon.sh
	restorecon -v /usr/local/bin/mydaemon /usr/lib/systemd/system

restart:
	sudo systemctl restart mydaemon

ausearch:
	sudo ausearch -m AVC -ts recent

sealert:
	sealert
	sudo ausearch -c 'mydaemon' --raw | audit2allow -M my-mydaemon
	sudo semodule -X 300 -i my-mydaemon.pp
	ausearch -m AVC -ts recent | audit2allow -R
	grep -r "logging_write_generic_logs" /usr/share/selinux/devel/include/ | grep .if
	cat /usr/share/selinux/devel/include/system/logging.if
	echo "logging_write_generic_logs(mydaemon_t)" >> mydaemon.te
	echo "allow mydaemon_t var_log_t:file { open write getattr };" >> mydaemon.te
	./mydaemon.sh

verification:
	ps -efZ | grep mydaemon
	ausearch -m AVC -ts recent

clean:
	sudo rm -f mydaemon
	sudo rm -rf mydaemon.fc mydaemon.if mydaemon.pp mydaemon_selinux* mydaemon.sh mydaemon.te noarch tmp
	sudo systemctl stop mydaemon
	sudo rm -f /usr/local/bin/mydaemon
	sudo rm -f /usr/lib/systemd/system/mydaemon.service
