# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2024-2025 Rong Tao
# test-linux Container Dockerfile
ARG IMAGE
FROM ${IMAGE}

MAINTAINER rongtao
ENV TZ=Asia/Shanghai

WORKDIR /root/tlbuild/
COPY ./scripts/install-deps.sh /root/tlbuild/
RUN ./install-deps.sh --all --force
