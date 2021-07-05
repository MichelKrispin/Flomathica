#include "Interpreter.h"

#include "llvm/IR/Verifier.h"
#include <iostream>

void Interpreter::visitProgram(Program* t) {} // abstract class
void Interpreter::visitDef(Def* t) {}         // abstract class
void Interpreter::visitCom(Com* t) {}         // abstract class
void Interpreter::visitStm(Stm* t) {}         // abstract class
void Interpreter::visitExp(Exp* t) {}         // abstract class

Interpreter::Interpreter() {
  TheContext = std::make_unique<llvm::LLVMContext>();
  TheModule = std::make_unique<llvm::Module>("Flomathica", *TheContext);
  Builder = std::make_unique<llvm::IRBuilder<>>(*TheContext);

  // Predefine some help
  HelpComments["exit()"] = "Exit the interpeter ('#' also works)";
  HelpComments["_toggle_ir()"] = "Toggle to show IR Code";
  HelpComments["_broom()"] = "Sweep everything off the screen";
  HelpComments["%"] = " X % Y : What is X % of Y";
}

void Interpreter::interpret(Visitable* v, bool print_llvm_ir) {

  // Before accepting the first create an anonymous function.
  // This should be removed if it is an actual function or
  // operator definition but if its an evaluated expression it
  // has to be called inside of a function
  std::vector<llvm::Type*> ArgumentTypes; // Empty arguments
  llvm::FunctionType* FunctionType =
      llvm::FunctionType::get(llvm::Type::getDoubleTy(*TheContext),
                              ArgumentTypes, false); // double @0()

  llvm::Function* Function =
      llvm::Function::Create(FunctionType, llvm::Function::ExternalLinkage,
                             "__anonymous_expr", *TheModule);

  // Create a new basic block to start insertion into.
  llvm::BasicBlock* AnonymousEmptyBB =
      llvm::BasicBlock::Create(*TheContext, "entry", Function);
  Builder->SetInsertPoint(AnonymousEmptyBB);

  v->accept(this);

  // If there are any errors make that clear
  if (errors.size() != 0) {
    std::cerr << "\033[91mPanic! Panic! Panic!\n";
    for (auto& error : errors) {
      std::cerr << "-> " << error << "\n";
    }
    std::cerr << "\033[0m";
    // Clear for next iteration
    errors.clear();
    return;
  }

  Function = TheModule->getFunction("__anonymous_expr");

  // If the anonymous function still exists add a return statement and call it
  if (Function != nullptr) {
    Builder->CreateRet(PassedOnVariable);

    // Verify it if it exists
    std::string output_string;
    llvm::raw_string_ostream rso(output_string);
    if (llvm::verifyFunction(*Function, &rso)) { // If True there is an error
      std::cerr << rso.str() << "\n";
    }

    // Print this before the anonymous function is removed
    if (print_llvm_ir) {
      TheModule->print(llvm::outs(), nullptr);
    }

    // Invoke the Just in Time Compiler and print the result
    std::cout << CompileJustInTime() << "\n";

    RemoveAnonymousExpressionFunction(); // Remove the anonymous function then
                                         // for the next one
  } else {
    // Print the function or operator at the end if it should be printed
    if (print_llvm_ir) {
      TheModule->print(llvm::outs(), nullptr);
    }
  }
}

void Interpreter::visitPDefinitions(PDefinitions* p_definitions) {
  if (p_definitions->listdef_)
    p_definitions->listdef_->accept(this);
}

void Interpreter::visitDFunction(DFunction* d_function) {
  RemoveAnonymousExpressionFunction();
  VariableAllocations.clear(); // Clear for this function

  // If the function already exists bail out
  llvm::Function* Function = TheModule->getFunction(d_function->id_);
  if (Function != nullptr) {
    errors.push_back("Excuse me... " + d_function->id_ + " already exists");
    return;
  }

  // Put the number of ids as double into the arguments
  std::vector<llvm::Type*> ArgumentTypes;
  ArgumentTypes.reserve(d_function->listid_->size());
  for (uint64_t i = 0; i < d_function->listid_->size(); ++i) {
    ArgumentTypes.push_back(llvm::Type::getDoubleTy(*TheContext));
  }

  llvm::FunctionType* FunctionType = llvm::FunctionType::get(
      llvm::Type::getDoubleTy(*TheContext), ArgumentTypes, false);

  Function =
      llvm::Function::Create(FunctionType, llvm::Function::ExternalLinkage,
                             d_function->id_, *TheModule);

  // Create a new basic block to start insertion into
  llvm::BasicBlock* EntryBB =
      llvm::BasicBlock::Create(*TheContext, "entry", Function);
  Builder->SetInsertPoint(EntryBB);

  ArgumentNames.clear();
  if (d_function->listid_)
    d_function->listid_->accept(this);

  if (ArgumentNames.size() != d_function->listid_->size()) {
    errors.push_back("No no. Look: " + d_function->id_ + " wants exactly (!) " +
                     std::to_string(d_function->listid_->size()) +
                     " arguments and not " +
                     std::to_string(ArgumentNames.size()) + "...");
    return;
  }

  uint32_t index = 0;
  for (auto& Arg : Function->args()) {
    // Allocate all arguments right away
    llvm::AllocaInst* Alloca =
        CreateEntryBlockAlloca(Function, ArgumentNames[index]);
    Builder->CreateStore(&Arg, Alloca);
    VariableAllocations[ArgumentNames[index]] = Alloca;

    Arg.setName("arg." + ArgumentNames[index]);
    index++;
  }

  // Create default comment
  PassedUpComment = "Help string looks empty... " + d_function->id_ + " wants ";
  if (d_function->listid_->size() == 0) {
    PassedUpComment += "no arguments";
  } else {
    for (auto& Name : ArgumentNames) {
      PassedUpComment += Name + " ";
    }
  }
  // Then it might be there
  if (d_function->com_)
    d_function->com_->accept(this);
  HelpComments[d_function->id_] = PassedUpComment;

  if (d_function->liststm_)
    d_function->liststm_->accept(this);
  if (d_function->exp_)
    d_function->exp_->accept(this);

  Builder->CreateRet(PassedOnVariable);
  // Verify it
  std::string output_string;
  llvm::raw_string_ostream rso(output_string);
  if (llvm::verifyFunction(*Function, &rso)) { // Error if true
    std::cerr << rso.str() << "\n";
  }
}

void Interpreter::visitDOperator(DOperator* d_operator) {
  RemoveAnonymousExpressionFunction();
  VariableAllocations.clear(); // Clear for this operator

  const std::string operator_prefix = "op_";

  // If there is already an operator with that name
  llvm::Function* Function =
      TheModule->getFunction(operator_prefix + d_operator->id_1);
  if (Function != nullptr) {
    errors.push_back("Excuse me... " + d_operator->id_1 + " already exists");
    return;
  }

  // visitId(d_operator->id_1);
  // visitId(d_operator->id_2);
  // visitId(d_operator->id_3);

  // Create a function with two arguments
  std::vector<llvm::Type*> ArgumentTypes;
  ArgumentTypes.push_back(llvm::Type::getDoubleTy(*TheContext));
  ArgumentTypes.push_back(llvm::Type::getDoubleTy(*TheContext));

  llvm::FunctionType* FunctionType = llvm::FunctionType::get(
      llvm::Type::getDoubleTy(*TheContext), ArgumentTypes, false);

  Function =
      llvm::Function::Create(FunctionType, llvm::Function::ExternalLinkage,
                             d_operator->id_1, *TheModule);

  llvm::BasicBlock* EntryBB =
      llvm::BasicBlock::Create(*TheContext, "entry", Function);
  Builder->SetInsertPoint(EntryBB);

  // Name the arguments correctly and allocate them
  uint32_t index = 0;
  for (auto& Arg : Function->args()) {
    if (index == 0) { // Very elegant...
      llvm::AllocaInst* Alloca =
          CreateEntryBlockAlloca(Function, d_operator->id_2);
      Builder->CreateStore(&Arg, Alloca);
      VariableAllocations[d_operator->id_2] = Alloca;
      Arg.setName("arg." + d_operator->id_2);
    } else {
      llvm::AllocaInst* Alloca =
          CreateEntryBlockAlloca(Function, d_operator->id_3);
      Builder->CreateStore(&Arg, Alloca);
      VariableAllocations[d_operator->id_3] = Alloca;
      Arg.setName("arg." + d_operator->id_3);
    }
    index++;
  }

  // Ignore the integer right now
  // visitInteger(d_operator->integer_);

  // Create default comment
  PassedUpComment =
      "Looks empty... Nobody knows what " + d_operator->id_1 + " is doing";
  if (d_operator->com_)
    d_operator->com_->accept(this);
  HelpComments[d_operator->id_1] = PassedUpComment;

  if (d_operator->liststm_)
    d_operator->liststm_->accept(this);
  if (d_operator->exp_) // The return expression
    d_operator->exp_->accept(this);

  Builder->CreateRet(PassedOnVariable);
  // Verify it
  std::string output_string;
  llvm::raw_string_ostream rso(output_string);
  if (llvm::verifyFunction(*Function, &rso)) { // Error if true
    std::cerr << rso.str() << "\n";
  }
}

void Interpreter::visitDHelp(DHelp* d_help) {
  RemoveAnonymousExpressionFunction(); // Do not invoke JIT

  // If there is something inside of the help then output that
  // Otherwise output default message
  if (d_help->string_.empty()) {
    PrintAllHelp();
  } else if (HelpComments.count(d_help->string_) != 0) {
    std::cout << HelpComments[d_help->string_] << "\n";
  } else {
    std::cout << "Nix da. Sogar der Ordner mit den vordefinierten Funktionen "
                 "ist leer...\n";
  }
  // visitString(d_help->string_);
}

void Interpreter::visitDExpression(DExpression* d_expression) {

  if (d_expression->exp_)
    d_expression->exp_->accept(this);
}

void Interpreter::visitCComment(CComment* c_comment) {
  PassedUpComment = c_comment->string_;
  // visitString(c_comment->string_);
}

void Interpreter::visitCEmpty(CEmpty* c_empty) {}

void Interpreter::visitSExpression(SExpression* s_expression) {

  if (s_expression->exp_)
    s_expression->exp_->accept(this);
}

void Interpreter::visitSInit(SInit* s_init) {
  if (errors.size() != 0) {
    return;
  }

  // visitId(s_init->id_);
  // If it does not exist create it

  llvm::Value* LeftVariable = nullptr;
  // If the variable does not yet exist then create it
  if (VariableAllocations.count(s_init->id_) == 0) {
    LeftVariable = CreateEntryBlockAlloca(
        Builder->GetInsertBlock()->getParent(), s_init->id_);
    VariableAllocations[s_init->id_] = LeftVariable;
  } else {
    LeftVariable = VariableAllocations[s_init->id_];
  }

  if (s_init->exp_)
    s_init->exp_->accept(this);

  Builder->CreateStore(PassedOnVariable, LeftVariable);
}

void Interpreter::visitSIfElse(SIfElse* s_if_else) {

  llvm::Function* Function = Builder->GetInsertBlock()->getParent();
  llvm::BasicBlock* ThenBB =
      llvm::BasicBlock::Create(*TheContext, "then", Function);
  llvm::BasicBlock* ElseBB =
      llvm::BasicBlock::Create(*TheContext, "else", Function);
  llvm::BasicBlock* ContinueBB =
      llvm::BasicBlock::Create(*TheContext, "continue", Function);

  if (s_if_else->exp_)
    s_if_else->exp_->accept(this);

  llvm::Value* Condition = Builder->CreateFCmpONE(
      PassedOnVariable, llvm::ConstantFP::get(*TheContext, llvm::APFloat(0.0)));
  Builder->CreateCondBr(Condition, ThenBB, ElseBB);

  Function->getBasicBlockList().push_back(ThenBB);
  Builder->SetInsertPoint(ThenBB);

  if (s_if_else->stm_1)
    s_if_else->stm_1->accept(this);

  Builder->CreateBr(ContinueBB);

  Function->getBasicBlockList().push_back(ElseBB);
  Builder->SetInsertPoint(ElseBB);

  if (s_if_else->stm_2)
    s_if_else->stm_2->accept(this);

  Builder->CreateBr(ContinueBB);

  Function->getBasicBlockList().push_back(ContinueBB);
  Builder->SetInsertPoint(ContinueBB);
}

void Interpreter::visitEDouble(EDouble* e_double) {

  visitDouble(e_double->double_);
}

void Interpreter::visitEInteger(EInteger* e_integer) {

  visitInteger(e_integer->integer_);
}

void Interpreter::visitEId(EId* e_id) {
  if (VariableAllocations.count(e_id->id_) == 0) {
    errors.push_back("Hey... " + e_id->id_ + " does not exist.");
  } else {
    visitId(e_id->id_);
  }
}

void Interpreter::visitECall(ECall* e_call) {
  if (errors.size() != 0) {
    return;
  }

  llvm::Function* Function = TheModule->getFunction(e_call->id_);
  if (Function == nullptr) {
    errors.push_back("Watch out dude! " + e_call->id_ + " does not exist.");
    return;
  }
  // visitId(e_call->id_);

  ArgumentVariables.clear();
  if (e_call->listexp_)
    e_call->listexp_->accept(this);
  if (ArgumentVariables.size() != Function->arg_size()) {
    errors.push_back("Why are there " +
                     std::to_string(ArgumentVariables.size()) +
                     " arguments, although " + e_call->id_ + " wants exactly " +
                     std::to_string(Function->arg_size()) + " arguments");
    return;
  }

  PassedOnVariable = Builder->CreateCall(Function, ArgumentVariables);
}

void Interpreter::visitEUMinus(EUMinus* eu_minus) {

  if (eu_minus->exp_)
    eu_minus->exp_->accept(this);

  PassedOnVariable = Builder->CreateFSub(
      llvm::ConstantFP::get(*TheContext, llvm::APFloat(0.0)), PassedOnVariable);
}

void Interpreter::visitETimes(ETimes* e_times) {

  if (e_times->exp_1)
    e_times->exp_1->accept(this);
  llvm::Value* LeftVariable = PassedOnVariable;

  if (e_times->exp_2)
    e_times->exp_2->accept(this);
  llvm::Value* RightVariable = PassedOnVariable;

  PassedOnVariable = Builder->CreateFMul(LeftVariable, RightVariable, "cmpmul");
}

void Interpreter::visitEDiv(EDiv* e_div) {

  if (e_div->exp_1)
    e_div->exp_1->accept(this);
  llvm::Value* LeftVariable = PassedOnVariable;

  if (e_div->exp_2)
    e_div->exp_2->accept(this);
  llvm::Value* RightVariable = PassedOnVariable;

  PassedOnVariable = Builder->CreateFDiv(LeftVariable, RightVariable, "cmpdiv");
}

void Interpreter::visitEPlus(EPlus* e_plus) {

  if (e_plus->exp_1)
    e_plus->exp_1->accept(this);
  llvm::Value* LeftVariable = PassedOnVariable;

  if (e_plus->exp_2)
    e_plus->exp_2->accept(this);
  llvm::Value* RightVariable = PassedOnVariable;

  PassedOnVariable = Builder->CreateFAdd(LeftVariable, RightVariable, "cmpadd");
}

void Interpreter::visitEMinus(EMinus* e_minus) {

  if (e_minus->exp_1)
    e_minus->exp_1->accept(this);
  llvm::Value* LeftVariable = PassedOnVariable;

  if (e_minus->exp_2)
    e_minus->exp_2->accept(this);
  llvm::Value* RightVariable = PassedOnVariable;

  PassedOnVariable = Builder->CreateFSub(LeftVariable, RightVariable, "cmpsub");
}

void Interpreter::visitELt(ELt* e_lt) {

  if (e_lt->exp_1)
    e_lt->exp_1->accept(this);
  llvm::Value* LeftVariable = PassedOnVariable;

  if (e_lt->exp_2)
    e_lt->exp_2->accept(this);
  llvm::Value* RightVariable = PassedOnVariable;

  PassedOnVariable =
      Builder->CreateFCmpOLT(LeftVariable, RightVariable, "cmplt");
  PassedOnVariable = Builder->CreateUIToFP(
      PassedOnVariable, llvm::Type::getDoubleTy(*TheContext), "fpcmpcast");
}

void Interpreter::visitEGt(EGt* e_gt) {

  if (e_gt->exp_1)
    e_gt->exp_1->accept(this);
  llvm::Value* LeftVariable = PassedOnVariable;

  if (e_gt->exp_2)
    e_gt->exp_2->accept(this);
  llvm::Value* RightVariable = PassedOnVariable;

  PassedOnVariable =
      Builder->CreateFCmpOGT(LeftVariable, RightVariable, "cmpgt");
  PassedOnVariable = Builder->CreateUIToFP(
      PassedOnVariable, llvm::Type::getDoubleTy(*TheContext), "fpcmpcast");
}

void Interpreter::visitELtEq(ELtEq* e_lt_eq) {

  if (e_lt_eq->exp_1)
    e_lt_eq->exp_1->accept(this);
  llvm::Value* LeftVariable = PassedOnVariable;

  if (e_lt_eq->exp_2)
    e_lt_eq->exp_2->accept(this);
  llvm::Value* RightVariable = PassedOnVariable;

  PassedOnVariable =
      Builder->CreateFCmpOLE(LeftVariable, RightVariable, "cmple");
  PassedOnVariable = Builder->CreateUIToFP(
      PassedOnVariable, llvm::Type::getDoubleTy(*TheContext), "fpcmpcast");
}

void Interpreter::visitEGtEq(EGtEq* e_gt_eq) {

  if (e_gt_eq->exp_1)
    e_gt_eq->exp_1->accept(this);
  llvm::Value* LeftVariable = PassedOnVariable;

  if (e_gt_eq->exp_2)
    e_gt_eq->exp_2->accept(this);
  llvm::Value* RightVariable = PassedOnVariable;

  PassedOnVariable =
      Builder->CreateFCmpOGE(LeftVariable, RightVariable, "cmpge");
  PassedOnVariable = Builder->CreateUIToFP(
      PassedOnVariable, llvm::Type::getDoubleTy(*TheContext), "fpcmpcast");
}

void Interpreter::visitEEq(EEq* e_eq) {

  if (e_eq->exp_1)
    e_eq->exp_1->accept(this);
  llvm::Value* LeftVariable = PassedOnVariable;

  if (e_eq->exp_2)
    e_eq->exp_2->accept(this);
  llvm::Value* RightVariable = PassedOnVariable;

  PassedOnVariable =
      Builder->CreateFCmpOEQ(LeftVariable, RightVariable, "cmpeq");
  PassedOnVariable = Builder->CreateUIToFP(
      PassedOnVariable, llvm::Type::getDoubleTy(*TheContext), "fpcmpcast");
}

void Interpreter::visitENEq(ENEq* en_eq) {

  if (en_eq->exp_1)
    en_eq->exp_1->accept(this);
  llvm::Value* LeftVariable = PassedOnVariable;

  if (en_eq->exp_2)
    en_eq->exp_2->accept(this);
  llvm::Value* RightVariable = PassedOnVariable;

  PassedOnVariable =
      Builder->CreateFCmpONE(LeftVariable, RightVariable, "cmpneq");
  PassedOnVariable = Builder->CreateUIToFP(
      PassedOnVariable, llvm::Type::getDoubleTy(*TheContext), "fpcmpcast");
}

void Interpreter::visitEPercentage(EPercentage* e_percentage) {

  if (e_percentage->exp_1)
    e_percentage->exp_1->accept(this);
  llvm::Value* LeftVariable = PassedOnVariable;

  if (e_percentage->exp_2)
    e_percentage->exp_2->accept(this);
  llvm::Value* RightVariable = PassedOnVariable;

  // Divide right side by hundred
  PassedOnVariable = Builder->CreateFDiv(
      RightVariable, llvm::ConstantFP::get(*TheContext, llvm::APFloat(100.0)),
      "cmpdiv");

  // Then multiply the result with the left side
  PassedOnVariable =
      Builder->CreateFMul(LeftVariable, PassedOnVariable, "cmpperc");
}

void Interpreter::visitEOperator(EOperator* e_operator) {
  if (errors.size() != 0) {
    return;
  }

  llvm::Function* Function = TheModule->getFunction(e_operator->id_);
  if (Function == nullptr) {
    errors.push_back("But but... " + e_operator->id_ + " does not exist.");
    return;
  }

  std::vector<llvm::Value*> Operands;
  if (e_operator->exp_1)
    e_operator->exp_1->accept(this);
  Operands.push_back(PassedOnVariable);

  // visitId(e_operator->id_);
  if (e_operator->exp_2)
    e_operator->exp_2->accept(this);

  Operands.push_back(PassedOnVariable);
  PassedOnVariable = Builder->CreateCall(Function, Operands);
}

void Interpreter::visitListDef(ListDef* list_def) {
  for (ListDef::iterator i = list_def->begin(); i != list_def->end(); ++i) {
    (*i)->accept(this);
  }
}

void Interpreter::visitListStm(ListStm* list_stm) {
  for (ListStm::iterator i = list_stm->begin(); i != list_stm->end(); ++i) {
    (*i)->accept(this);
  }
}

void Interpreter::visitListExp(ListExp* list_exp) {
  for (ListExp::iterator i = list_exp->begin(); i != list_exp->end(); ++i) {
    (*i)->accept(this);
    ArgumentVariables.push_back(PassedOnVariable);
  }
}

void Interpreter::visitListId(ListId* list_id) {
  for (ListId::iterator i = list_id->begin(); i != list_id->end(); ++i) {
    // visitId(*i);
    // The only place where this list thing is called is inside the arguments
    ArgumentNames.push_back(*i);
  }
}

void Interpreter::visitInteger(Integer x) {
  PassedOnVariable =
      llvm::ConstantFP::get(*TheContext, llvm::APFloat(static_cast<double>(x)));
}

void Interpreter::visitChar(Char x) {}

void Interpreter::visitDouble(Double x) {
  PassedOnVariable = llvm::ConstantFP::get(*TheContext, llvm::APFloat(x));
}

void Interpreter::visitString(String x) {}

void Interpreter::visitIdent(Ident x) {}

void Interpreter::visitId(Id x) {
  // If there is any variable that might exist load it up
  if (VariableAllocations.count(x) != 0) {
    PassedOnVariable = Builder->CreateLoad(VariableAllocations[x]);
  }
}
