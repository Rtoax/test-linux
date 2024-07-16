SHELL = bash

# SPDX-License-Identifier: GPL-2.0
CC = gcc
CFLAGS = -O2 -Wall -pthread

all: trace-agent

.c.o:
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	@$(CC) $(CFLAGS) -c $^ -o $@

trace-agent: trace-agent.o trace-agent-ctl.o trace-agent-rw.o
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	@$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o trace-agent
