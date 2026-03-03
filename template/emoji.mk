# SPDX-License-Identifier: GPL-3.0
# Copyright (C) 2025-2026 Rong Tao
ifndef _EMOJI_MK
_EMOJI_MK = 1

EMOJI_MOONS := 🌑 🌒 🌓 🌔 🌕 🌖 🌗 🌘 🌑
EMOJI_LOCK := 🔒
EMOJI_UNLOCK := 🔓
EMOJI_KEY := 🔑

EMOJI_WARNING := ⚠️

# MORE: ✓ ✔ ✗ ✘ ☓ ✕ ✖ 〤 √ ☐ ☑ ☒ ✅ ❎ ❌
EMOJI_CHECK := ✅
EMOJI_CROSS := ❌

EMOJI_PENDING := ⏳

EMOJI_ROBOT := 🤖
EMOJI_AIRPLANE := ✈️

EMOJI_HEART := ❤

EMOJI_FIRE := 🔥

ifdef DEBUG
  $(info EMOJI ${EMOJI_MOONS}${EMOJI_LOCK}${EMOJI_UNLOCK}${EMOJI_KEY} \
         ${EMOJI_WARNING}${EMOJI_CHECK}${EMOJI_CROSS}${EMOJI_AIRPLANE} \
         ${EMOJI_HEART}${EMOJI_FIRE}${EMOJI_PENDING}${EMOJI_ROBOT})
endif

endif
