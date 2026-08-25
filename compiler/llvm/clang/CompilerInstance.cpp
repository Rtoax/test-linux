#include <clang/Driver/Driver.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <iostream>

int main(void)
{
	std::string errstr;
	llvm::raw_string_ostream err(errstr);

	llvm::IntrusiveRefCntPtr<llvm::vfs::InMemoryFileSystem> vfs(
		new llvm::vfs::InMemoryFileSystem());

	std::vector<const char *> args;
	args.push_back("-O0");
	args.push_back("-I.");

	static std::shared_ptr<clang::DiagnosticOptions> diagOpts =
		std::make_shared<clang::DiagnosticOptions>();
	llvm::IntrusiveRefCntPtr<clang::DiagnosticIDs> diagID(
		new clang::DiagnosticIDs());
	auto client =
		std::make_unique<clang::TextDiagnosticPrinter>(err, *diagOpts);
	auto diags = std::make_unique<clang::DiagnosticsEngine>(
		diagID, *diagOpts, client.release());

	auto inv = std::make_shared<clang::CompilerInvocation>();
	inv->getTargetOpts().Triple = "bpf";
	inv->getCodeGenOpts().setDebugInfo(llvm::codegenoptions::FullDebugInfo);
	inv->getCodeGenOpts().DebugColumnInfo = true;

	clang::CompilerInvocation::CreateFromArgs(
		*inv, llvm::ArrayRef<const char *>(args), *diags);

	clang::CompilerInstance ci;
	ci.getInvocation() = *inv;
	ci.setDiagnostics(diags.release());
	/* LLVM_VERSION_MAJOR >= 22 */
	ci.setVirtualFileSystem(vfs);
	ci.createFileManager();
	ci.createSourceManager();

	/* TODO: bpftrace/src/ast/passes/clang_build.cpp */

	return 0;
}
