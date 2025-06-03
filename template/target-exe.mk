# SPDX-License-Identifier: GPL-3.0
CC ?= gcc
CXX ?= g++
Q ?= @

${OUTPUT}%.o: %.c | ${OUTPUT}
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

${OUTPUT}%.c.s: %.c | ${OUTPUT}
	@echo -e "  CC S \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}LD_LIBRARY_PATH=$(shell pwd) $(CC) -S -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}LD_LIBRARY_PATH=$(shell pwd) $(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*))

${OUTPUT}%.opp: %.cpp | ${OUTPUT}
	@echo -e "  CXX  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CXX) -o $(@) -c $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

${OUTPUT}%.cpp.s: %.cpp | ${OUTPUT}
	@echo -e "  CXX S  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CXX) -S -o $(@) -c $(<) $(CXXFLAGS) $(CXXFLAGS_$(*))

${TARGETS_CPP}: %:
	@echo -e "  LD CXX   \033[1;32m$(@)\033[m"
	${Q}$(CXX) -o $(@) $(^) $(LDXXFLAGS) $(LDXXFLAGS_$(*))
