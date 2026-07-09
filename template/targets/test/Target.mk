foo.h:
	$(call log_obj,DEP,${@})
	${Q}echo "void foo(void);" > foo.h

bar.h:
	$(call log_obj,DEP,${@})
	${Q}echo "void bar(void);" > bar.h
