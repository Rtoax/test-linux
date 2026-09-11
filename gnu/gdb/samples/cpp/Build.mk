target-cpp-y := global-var

CXXFLAGS += -O0 -ggdb
LDXXFLAGS += -pthread

prog-y += global-var.sh
