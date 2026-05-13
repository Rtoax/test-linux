include k8s.mk
include prometheus.mk

subdir-${HAVE_K8S} += kubernetes
subdir-${HAVE_PROMETHEUS} += prometheus
