#ifndef INTERPRETER_HEADER
#define INTERPRETER_HEADER

#include "../Parser/Absyn.H"

#include <iostream>
#include <map>

#include "llvm/ADT/APFloat.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Utils/Cloning.h"

class Interpreter : public Visitor {
public:
  Interpreter();

  void interpret(Visitable* v, bool print_llvm_ir = false);

  void visitProgram(Program* p) override;
  void visitDef(Def* p) override;
  void visitCom(Com* p) override;
  void visitStm(Stm* p) override;
  void visitExp(Exp* p) override;
  void visitPDefinitions(PDefinitions* p) override;
  void visitDFunction(DFunction* p) override;
  void visitDOperator(DOperator* p) override;
  void visitDHelp(DHelp* p) override;
  void visitDExpression(DExpression* p) override;
  void visitCComment(CComment* p) override;
  void visitCEmpty(CEmpty* p) override;
  void visitSExpression(SExpression* p) override;
  void visitSInit(SInit* p) override;
  void visitSIfElse(SIfElse* p) override;
  void visitEDouble(EDouble* p) override;
  void visitEInteger(EInteger* p) override;
  void visitEId(EId* p) override;
  void visitECall(ECall* p) override;
  void visitEUMinus(EUMinus* p) override;
  void visitETimes(ETimes* p) override;
  void visitEDiv(EDiv* p) override;
  void visitEPlus(EPlus* p) override;
  void visitEMinus(EMinus* p) override;
  void visitELt(ELt* p) override;
  void visitEGt(EGt* p) override;
  void visitELtEq(ELtEq* p) override;
  void visitEGtEq(EGtEq* p) override;
  void visitEEq(EEq* p) override;
  void visitENEq(ENEq* p) override;
  void visitEPercentage(EPercentage* p) override;
  void visitEOperator(EOperator* p) override;
  void visitListDef(ListDef* p) override;
  void visitListStm(ListStm* p) override;
  void visitListExp(ListExp* p) override;
  void visitListId(ListId* p) override;

  void visitInteger(Integer x) override;
  void visitChar(Char x) override;
  void visitDouble(Double x) override;
  void visitString(String x) override;
  void visitIdent(Ident x) override;
  void visitId(Id x) override;

private:
  std::map<std::string, llvm::Value*> VariableAllocations;
  llvm::Value* PassedOnVariable;
  std::vector<std::string> ArgumentNames;
  std::vector<llvm::Value*> ArgumentVariables;
  std::vector<std::string> errors;
  std::string PassedUpComment;
  std::map<std::string, std::string> HelpComments;

  std::unique_ptr<llvm::LLVMContext> TheContext; //< Global context
  std::unique_ptr<llvm::Module> TheModule;       //< The module
  std::unique_ptr<llvm::IRBuilder<>> Builder; //< The intermediate repr builder

private:
  /**
   *  Create an allocation instruction in the entry block of a function
   * for mutable variables.
   */
  llvm::AllocaInst* CreateEntryBlockAlloca(llvm::Function* TheFunction,
                                           const std::string& Id) {
    llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(),
                           TheFunction->getEntryBlock().begin());
    return TmpB.CreateAlloca(llvm::Type::getDoubleTy(*TheContext), 0,
                             Id.c_str());
  }

  /**
   * Looks for a function with the name "__anonymous_expr"
   * and if it exists it will be removed.
   */
  void RemoveAnonymousExpressionFunction() {
    llvm::Function* Function = TheModule->getFunction("__anonymous_expr");
    if (Function != nullptr) {
      Function->eraseFromParent();
    }
  }

  /**
   * Compiles TheModule just in time and returns the result of
   * the anonymous expression function.
   */
  double CompileJustInTime() {
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();
    LLVMInitializeNativeAsmPrinter();

    // Pass a cloned module with the anonymous function to the execution engine

    std::unique_ptr<llvm::Module> AnonymousModule =
        llvm::CloneModule(*TheModule);
    llvm::Function* Function = AnonymousModule->getFunction("__anonymous_expr");

    llvm::ExecutionEngine* EE =
        llvm::EngineBuilder(std::move(AnonymousModule)).create();

    std::vector<llvm::GenericValue> noargs;
    llvm::GenericValue gv = EE->runFunction(Function, noargs);

    // Import result of execution:
    double result = gv.DoubleVal;
    delete EE;
    return result;
  }

  /**
   * Print all existing help functions
   */
  void PrintAllHelp() {
    if (HelpComments.empty()) {
      std::cout << "Sorry. Ueberhaupt nichts zu sehen hier.\n";
      return;
    }

    std::cout << "? \"<function-name>\" to get specific help\n\n";
    for (auto const& value : HelpComments) {
      std::cout << " - " << value.first << ": " << value.second << "\n";
    }
  }
};

#endif
