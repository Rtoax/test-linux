# test-linux Container Dockerfile
#
# Copyright (C) 2024 Rong Tao
#
ARG IMAGE
FROM ${IMAGE}

WORKDIR /root/tlbuild/
COPY ./scripts/install-deps.sh /root/tlbuild/
RUN ./install-deps.sh --all --allowerasing
