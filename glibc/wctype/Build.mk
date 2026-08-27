target-y := wchar_t
target-y += iswctype
target-y += wcstol
target-y += demo-1

prog-y += ${target-y}

LDFLAGS += -pthread
