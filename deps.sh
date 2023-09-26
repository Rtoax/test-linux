#!/bin/bash

pkgs=( make cmake gcc clang )

sudo dnf install -y ${pkgs[@]}
