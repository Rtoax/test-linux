target-y += ftime

prog-y += ${target-y}

CFLAGS_ftime := -Wno-deprecated-declarations
