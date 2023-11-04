
TARGETS += builder
TARGETS += button button2
TARGETS += button_keyboard
TARGETS += button_image button_image2
TARGETS += radiobutton
TARGETS += checkbutton
TARGETS += arrow_button
TARGETS += button_fixed_move
TARGETS += button_boxs
TARGETS += drawing
TARGETS += grid
TARGETS += label
TARGETS += hello
TARGETS += image
TARGETS += window window_2nd scrolled_window
TARGETS += statusbar
TARGETS += frame aspect_frame

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

# TODO: no deprecated
CFLAGS += -Wno-error=deprecated-declarations

.PHONY: build
build: ${TARGETS}
	@echo
	@echo -e " \033[1;33m Done \033[m"

# Add more object.o file
builder: builder.o
arrow_button: arrow_button.o
button: button.o
button2: button2.o
button_keyboard: button_keyboard.o
button_image: button_image.o
button_image2: button_image2.o
radiobutton: radiobutton.o
checkbutton: checkbutton.o
button_fixed_move: button_fixed_move.o
button_boxs: button_boxs.o
label: label.o
drawing: drawing.o
grid: grid.o
hello: hello.o
image: image.o
window: window.o
window_2nd: window_2nd.o
scrolled_window: scrolled_window.o
statusbar: statusbar.o
frame: frame.o
aspect_frame: aspect_frame.o

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
