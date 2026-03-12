target-y += tcp-server tcp-client tcp-server-noclose
target-y += udp-server udp-client

CFLAGS_tcp-server-noclose := -DNO_CLOSE_CLIENT_FD=1
