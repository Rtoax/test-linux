SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q



all:
	./base64.sh
	./rand.sh

clean:
	rm -rf *.pem
