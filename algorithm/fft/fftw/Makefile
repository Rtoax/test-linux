FFTW_HDR = /usr/include/fftw3.h

TARGETS :=
ifneq ($(wildcard ${FFTW_HDR}),)
  TARGETS += fftw_plan_dft_1d
  TARGETS += fftw_plan_dft_1d-1
  TARGETS += fftw_plan_dft_r2c_1d

  LDFLAGS += -lfftw3
else
  $(warning "Not found header ${FFTW_HDR}, please install fftw")
endif

LDFLAGS += -lm

include ../../../template/main.mk

fftw_plan_dft_1d: fftw_plan_dft_1d.o
fftw_plan_dft_1d-1: fftw_plan_dft_1d-1.o
fftw_plan_dft_r2c_1d: fftw_plan_dft_r2c_1d.o
