ifndef TEST_MAK_DEF_1
  $(error Not defined TEST_MAK_DEF_1)
else
  $(info TEST_MAK_DEF_1=${TEST_MAK_DEF_1})
endif

.PHONY: build
build:
