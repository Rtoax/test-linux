target-y += ffat-lto-objects
target-y += flto

prog-y += ${target-y}

CFLAGS_ffat-lto-objects := -flto -ffat-lto-objects
CFLAGS_flto := -flto=auto
LDFLAGS_flto := -flto=auto
