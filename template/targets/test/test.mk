ifndef TEST_MK_DEF_1
  $(error Not defined TEST_MK_DEF_1)
else
  $(info TEST_MK_DEF_1=${TEST_MK_DEF_1})
endif

.PHONY: build
build:
