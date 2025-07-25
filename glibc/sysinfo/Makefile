targets :=
targets += sysinfo
targets += get_avphys_pages get_phys_pages
targets += get_nprocs get_nprocs_conf

CFLAGS :=
CFLAGS += -I../../../
CFLAGS += -lm

include ../../template/main.mk

sysinfo: sysinfo.o
get_avphys_pages: get_avphys_pages.o
get_phys_pages: get_phys_pages.o
get_nprocs: get_nprocs.o
get_nprocs_conf: get_nprocs_conf.o
