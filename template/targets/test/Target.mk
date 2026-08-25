foo.h:
	@$(call log_obj,DEP,${@})
	${Q}echo "void foo(void);" > foo.h
foo.hpp:
	@$(call log_obj,DEP,${@})
	${Q}echo "void foo(void);" > foo.hpp

bar.h:
	@$(call log_obj,DEP,${@})
	${Q}echo "void bar(void);" > bar.h
bar.hpp:
	@$(call log_obj,DEP,${@})
	${Q}echo "void bar(void);" > bar.hpp
