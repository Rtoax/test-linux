targets :=
targets += shmctl
targets += reader
targets += writer writer-hugetlb
targets += private

CFLAGS_writer-hugetlb := -DHAVE_HUGETLB=1

include ../../../template/main.mk

shmctl: shmctl.o
reader: reader.o
writer: writer.o
writer-hugetlb: writer-hugetlb.o
private: private.o
