#!/bin/bash
set -e

sudo podman ps --format "{{.ID}}"
