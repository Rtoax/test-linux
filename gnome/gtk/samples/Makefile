TARGETS :=
TARGETS += builder
TARGETS += builder-menu
TARGETS += button button2
TARGETS += button_keyboard
TARGETS += button_image button_image2
TARGETS += radiobutton
TARGETS += calculater
TARGETS += checkbutton
TARGETS += arrow_button
TARGETS += button_fixed_move
TARGETS += button_boxs
TARGETS += spin_button
TARGETS += drawing drawing_pic
TARGETS += grid
TARGETS += label
TARGETS += hello
TARGETS += image
TARGETS += window window_2nd scrolled_window
TARGETS += statusbar
TARGETS += frame aspect_frame
TARGETS += menu
TARGETS += dialog
TARGETS += sunny
TARGETS += entry_get_text

CC := gcc

CFLAGS :=
LDFLAGS :=

GTK_VERSION := gtk+-3.0
GTK_LIBS := $(shell pkg-config --libs ${GTK_VERSION})
GTK_CFLAGS := $(shell pkg-config --cflags ${GTK_VERSION})

ifdef DEBUG
  $(info GTK_CFLAGS=$(GTK_CFLAGS))
  $(info GTK_LIBS=$(GTK_LIBS))
endif

CFLAGS += $(GTK_CFLAGS)
CFLAGS += $(GTK_LIBS)

LDFLAGS += $(GTK_LIBS)

# TODO: no deprecated
CFLAGS += -Wno-error=deprecated-declarations

include ../../../template/main.mk

builder: builder.o
builder-menu: builder-menu.o
arrow_button: arrow_button.o
button: button.o
button2: button2.o
button_keyboard: button_keyboard.o
button_image: button_image.o
button_image2: button_image2.o
calculater: calculater.o
radiobutton: radiobutton.o
checkbutton: checkbutton.o
button_fixed_move: button_fixed_move.o
button_boxs: button_boxs.o
entry_get_text: entry_get_text.o
spin_button: spin_button.o
sunny: sunny.o
label: label.o
drawing: drawing.o
drawing_pic: drawing_pic.o
grid: grid.o
hello: hello.o
image: image.o
window: window.o
window_2nd: window_2nd.o
scrolled_window: scrolled_window.o
statusbar: statusbar.o
frame: frame.o
aspect_frame: aspect_frame.o
menu: menu.o
dialog: dialog.o
