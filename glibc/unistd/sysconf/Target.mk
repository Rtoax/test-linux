confs_def.h: sysconf.sh
	${Q}./sysconf.sh

cleans:
	${Q}rm -f gen-sysconf-* confs_def.h
