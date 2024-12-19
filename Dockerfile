# SPDX-License-Identifier: GPL-3.0
# test-linux Container Dockerfile
#
# Copyright (C) 2024 Rong Tao
#
ARG IMAGE
FROM ${IMAGE}

MAINTAINER rongtao
ENV TZ=Asia/Shanghai

WORKDIR /root/tlbuild/
COPY ./scripts/install-deps.sh /root/tlbuild/
RUN ./install-deps.sh --all --allowerasing
