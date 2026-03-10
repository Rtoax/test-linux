target-y += builder
target-y += builder-menu
target-y += button button2
target-y += button_keyboard
target-y += button_image button_image2
target-y += radiobutton
target-y += calculater
target-y += checkbutton
target-y += arrow_button
target-y += button_fixed_move
target-y += button_boxs
target-y += spin_button
target-y += drawing drawing_pic
target-y += grid
target-y += label
target-y += hello
target-y += image
target-y += window window_2nd scrolled_window
target-y += statusbar
target-y += frame aspect_frame
target-y += menu
target-y += dialog
target-y += sunny
target-y += entry_get_text
target-y += deepseek

GTK_VERSION := gtk+-3.0
GTK_LIBS := $(shell pkg-config --libs ${GTK_VERSION})
GTK_CFLAGS := $(shell pkg-config --cflags ${GTK_VERSION})

ifdef DEBUG
  $(info GTK_CFLAGS=$(GTK_CFLAGS))
  $(info GTK_LIBS=$(GTK_LIBS))
endif

CFLAGS += $(GTK_CFLAGS)
LDFLAGS += $(GTK_LIBS)

# TODO: no deprecated
CFLAGS += -Wno-error=deprecated-declarations

include main.mk
