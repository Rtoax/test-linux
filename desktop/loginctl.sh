#!/bin/bash
set -e

loginctl terminate-session $XDG_SESSION_ID
