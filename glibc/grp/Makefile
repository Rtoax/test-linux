TARGETS :=
TARGETS += fgetgrent
TARGETS += getgrent
TARGETS += getgrgid
TARGETS += getgrnam
TARGETS += getgrouplist
TARGETS += initgroups
TARGETS += setgrent
TARGETS += getgroups
TARGETS += demo-pwd-grp

CFLAGS := -Werror -Wall -D_GNU_SOURCE

include ../../template/main.mk

fgetgrent: fgetgrent.o
getgrent: getgrent.o
getgrgid: getgrgid.o
getgrnam: getgrnam.o
getgrouplist: getgrouplist.o
initgroups: initgroups.o
setgrent: setgrent.o
getgroups: getgroups.o
demo-pwd-grp: demo-pwd-grp.o
