ifneq (${SRC_SFX_LIST}, 1 2 3 4 5 6 7 8 9 10 11 12 13)
  $(error SFX_MAX_N=${SFX_MAX_N}, SRC_SFX_LIST=${SRC_SFX_LIST} failed)
endif
