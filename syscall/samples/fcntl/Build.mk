target-y += fallocate
target-y += fadvise
target-y += open openat openat2
target-y += splice splice-read
target-y += O_ flags S_ mode

# F_ flags
target-y += F_GET_SEALS
target-y += F_ADD_SEALS
target-y += F_SETLKW
target-y += F_DUPFD
target-y += F_GETFD
target-y += F_GETFL
# O_ flags
target-y += O_CLOEXEC
target-y += O_PATH
target-y += O_TMPFILE

open-objs := fcntl_helpers.o
openat-objs := fcntl_helpers.o
openat2-objs := fcntl_helpers.o
F_SETLKW-objs := fcntl_helpers.o
