// SPDX-License-Identifier: GPL-3.0
/* Copyright (c) 2025 Rong Tao */
#include "clang/AST/ASTContext.h"
#include "clang/AST/Attr.h"
#include "clang/Sema/ParsedAttr.h"
#include "clang/Sema/Sema.h"
#include "clang/Sema/SemaDiagnostic.h"
#include "llvm/IR/Attributes.h"

#include "configs.hpp"

using namespace clang;

namespace fakecuda::frontend::attribute {

struct DeviceAttrInfo : public ParsedAttrInfo {
	DeviceAttrInfo() {
		/**
		 * Can take up to 0 optional arguments, to emulate accepting a
		 * variadic number of arguments. This just illustrates how many
		 * arguments a `ParsedAttrInfo` can hold.
		 */
		OptArgs = 15;
		/**
		 * GNU-style __attribute__(("device")) and C++/C23-style [[device]]
		 * and [[plugin::device]] supported.
		 */
		static constexpr Spelling S[] = {{ParsedAttr::AS_GNU, DEVICE_ATTR_NAME},
						 {ParsedAttr::AS_C23, DEVICE_ATTR_NAME},
						 {ParsedAttr::AS_CXX11, DEVICE_ATTR_NAME},
						 {ParsedAttr::AS_CXX11, "plugin::" DEVICE_ATTR_NAME}};
		Spellings = S;
	}

	bool diagAppertainsToDecl(Sema &S, const ParsedAttr &Attr,
				  const Decl *D) const override {
		/* This attribute appertains to functions, variable. */
		if (!isa<FunctionDecl>(D) && !isa<VarDecl>(D)) {
			unsigned ID = S.getDiagnostics().getCustomDiagID(DiagnosticsEngine::Error,
						"'" DEVICE_ATTR_NAME "' attribute only allowed at function and variable");
			S.Diag(Attr.getLoc(), ID);
			return false;
		}
		return true;
	}

	AttrHandling handleDeclAttribute(Sema &S, Decl *D,
					 const ParsedAttr &Attr) const override {
		/* Check if the decl is at file scope. */
		if (!D->getDeclContext()->isFileContext()) {
			unsigned ID = S.getDiagnostics().getCustomDiagID(DiagnosticsEngine::Error,
						"'" DEVICE_ATTR_NAME "' attribute only allowed at file scope");
			S.Diag(Attr.getLoc(), ID);
			return AttributeNotApplied;
		}

		/* No need arguments */
		if (Attr.getNumArgs() > 0) {
			unsigned ID = S.getDiagnostics().getCustomDiagID(DiagnosticsEngine::Error,
						"'" DEVICE_ATTR_NAME "' attribute no need arguments");
			S.Diag(Attr.getLoc(), ID);
			return AttributeNotApplied;
		}
		return AttributeApplied;
	}

	AttrHandling handleStmtAttribute(Sema &S, Stmt *St, const ParsedAttr &Attr,
				  class Attr *&Result) const override {

		if (Attr.getNumArgs() > 0) {
			unsigned ID = S.getDiagnostics().getCustomDiagID(
						DiagnosticsEngine::Error,
						"'" DEVICE_ATTR_NAME "' attribute no need arguments");
			S.Diag(Attr.getLoc(), ID);
			return AttributeNotApplied;
		} else {
			Result = AnnotateAttr::Create(S.Context, DEVICE_ATTR_NAME, nullptr, 0,
						Attr.getRange());
		}
		return AttributeApplied;
	}
};

} // namespace

static ParsedAttrInfoRegistry::Add<fakecuda::frontend::attribute::DeviceAttrInfo> X(DEVICE_ATTR_NAME, "");
