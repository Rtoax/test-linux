FFTW_HDR = /usr/include/fftw3.h

ifneq ($(wildcard ${FFTW_HDR}),)
  target-y += fftw_plan_dft_1d
  target-y += fftw_plan_dft_1d-1
  target-y += fftw_plan_dft_r2c_1d

  LDFLAGS += -lfftw3
else
  $(warning "Not found header ${FFTW_HDR}, please install fftw")
endif

LDFLAGS += -lm

include main.mk
