# SPDX-License-Identifier: GPL-3.0

define dep_bpf_skel
$(eval ${OUTPUT}${1}.o: ${OUTPUT}${1}.skel.h)
endef

$(foreach skel, ${target-y}, $(call dep_bpf_skel,${skel}))

# Extra depends
${OUTPUT}ring_buffer.o: ${OUTPUT}map_array.skel.h
${OUTPUT}socket_filter.o: ${OUTPUT}map_array.skel.h
${OUTPUT}tracepoint.o: ${OUTPUT}map_hash.skel.h
