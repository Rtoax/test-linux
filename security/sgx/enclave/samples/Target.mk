enclave_u.c: enclave_u.h
enclave_t.c: enclave_t.h

%_u.h:
	$(call log_obj,EDGER8R,$(@))
	${Q}${SGX_EDGER8R} --untrusted $(*).edl

%_t.h:
	$(call log_obj,EDGER8R,$(@))
	${Q}${SGX_EDGER8R} --trusted $(*).edl
