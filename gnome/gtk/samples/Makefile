
TARGETS += builder
TARGETS += button button2 button_keyboard button_image button_image2
TARGETS += drawing
TARGETS += grid
TARGETS += hello
TARGETS += image
TARGETS += window

DEBUG = yes
SRC_PATH := $(shell pwd)
CC = gcc

GTK_VERSION := gtk+-3.0
GTK_LIBS := $(shell pkg-config --libs gtk+-3.0)
GTK_CFLAGS := $(shell pkg-config --cflags gtk+-3.0)

CFLAGS := -Werror -Wall
CFLAGS += $(GTK_CFLAGS)
CFLAGS += $(GTK_LIBS)

ifdef DEBUG
CFLAGS += -DDEBUG -O0 -g
endif

.PHONY: build
build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
builder: builder.o
button: button.o
button2: button2.o
button_keyboard: button_keyboard.o
button_image: button_image.o
button_image2: button_image2.o
drawing: drawing.o
grid: grid.o
hello: hello.o
image: image.o
window: window.o

CFLAGS_button_keyboard := -Wno-error=deprecated-declarations
CFLAGS_button_image2 := -Wno-error=deprecated-declarations

%.o: %.c
	@echo -e "Compile  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "Target   \033[1;32m$(@)\033[m"
	$(CC) $(CFLAGS) -o $(@) $(^) $(STATIC_OPTS) $(LDLIBS)

test: ${TARGETS}
	@echo -e "Test   \033[1;32m$(@)\033[m"

.PHONY: clean
clean:
	@echo -e "Clean   \033[1;32m$(@)\033[m"
	@rm -f ${TARGETS} *.o *.d
