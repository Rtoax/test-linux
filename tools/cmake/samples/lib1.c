#ifndef CMAKE_SAMPLES
#error Not defined CMAKE_SAMPLES
#endif

#if !defined(__fedora__) && !defined(__ubuntu__) && !defined(__debian__) && \
	!defined(__cclinux__)
#error Must define __${distro}__
#endif
