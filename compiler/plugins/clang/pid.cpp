#include <clang/Frontend/FrontendPluginRegistry.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/AST/AST.h>
#include <clang/AST/ASTConsumer.h>
#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/Sema/Sema.h>
#include <clang/Sema/Lookup.h>
#include <clang/Sema/Scope.h>
#include <llvm/Support/raw_ostream.h>
#include <unistd.h>

using namespace clang;

class PidConsumer : public ASTConsumer {
private:
    CompilerInstance &CI;
    bool PidAdded = false;

public:
    PidConsumer(CompilerInstance &CI) : CI(CI) {}

    void HandleTranslationUnit(ASTContext &Ctx) override {
        if (PidAdded) return;
        
        addPidVariable(Ctx);
        PidAdded = true;
    }

private:
    void addPidVariable(ASTContext &Ctx) {
        Sema &S = CI.getSema();
        
        // 获取当前进程PID
        int currentPid = getpid();
        
        // 创建变量声明
        IdentifierInfo *II = &Ctx.Idents.get("pid");
        VarDecl *VD = VarDecl::Create(Ctx, 
                                     Ctx.getTranslationUnitDecl(),
                                     SourceLocation(), 
                                     SourceLocation(), 
                                     II, 
                                     Ctx.IntTy, 
                                     nullptr, 
                                     SC_None);
        
        // 创建初始化表达式
        Expr *Init = IntegerLiteral::Create(Ctx, 
                                           llvm::APInt(32, currentPid), 
                                           Ctx.IntTy, 
                                           SourceLocation());
        VD->setInit(Init);
        
        // 添加到全局作用域
        Ctx.getTranslationUnitDecl()->addDecl(VD);
        
        llvm::errs() << "Successfully added 'pid' variable with value: " << currentPid << "\n";
        
        // 验证变量已添加
        verifyPidVariable(Ctx);
    }
    
    void verifyPidVariable(ASTContext &Ctx) {
        llvm::errs() << "Verifying pid variable...\n";
        for (auto *D : Ctx.getTranslationUnitDecl()->decls()) {
            if (VarDecl *VD = dyn_cast<VarDecl>(D)) {
                if (VD->getName() == "pid") {
                    llvm::errs() << "Found pid variable: type=" 
                               << VD->getType().getAsString()
                               << ", hasInit=" << VD->hasInit() << "\n";
                    return;
                }
            }
        }
        llvm::errs() << "ERROR: pid variable not found in AST!\n";
    }
};

class PidPlugin : public PluginASTAction {
protected:
    std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &CI,
                                                  StringRef InFile) override {
        return std::make_unique<PidConsumer>(CI);
    }

    bool ParseArgs(const CompilerInstance &CI,
                  const std::vector<std::string> &Args) override {
        return true;
    }

    PluginASTAction::ActionType getActionType() override {
        return AddBeforeMainAction;
    }
};

static FrontendPluginRegistry::Add<PidPlugin>
    X("pid-plugin", "Adds built-in pid variable");
