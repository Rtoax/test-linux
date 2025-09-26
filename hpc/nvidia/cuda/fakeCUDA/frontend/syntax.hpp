// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#ifndef __FAKECUDA_FRONTEND_SYNTAX_H
#define __FAKECUDA_FRONTEND_SYNTAX_H	1

#include "clang/Basic/TokenKinds.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Parse/Parser.h"

namespace cudaSyntax {
	enum cudaTokens {
		TOK_TRIPLE_LESS = clang::tok::NUM_TOKENS,	// <<<
		TOK_TRIPLE_GREATER,	// >>>
		NUM_EXTRA_TOKENS,
	};
}

#endif
