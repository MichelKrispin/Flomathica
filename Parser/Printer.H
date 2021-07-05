#ifndef PRINTER_HEADER
#define PRINTER_HEADER

#include "Absyn.H"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* Certain applications may improve performance by changing the buffer size */
#define BUFFER_INITIAL 2000
/* You may wish to change _L_PAREN or _R_PAREN */
#define _L_PAREN '('
#define _R_PAREN ')'

class PrintAbsyn : public Visitor
{
 protected:
  int _n_, _i_;
  /* The following are simple heuristics for rendering terminals */
  /* You may wish to change them */
  void render(Char c);
  void render(String s);
  void render(const char *s);
  void indent(void);
  void backup(void);
 public:
  PrintAbsyn(void);
  ~PrintAbsyn(void);
  char *print(Visitable *v);

  void visitProgram(Program *p); /* abstract class */
  void visitPDefinitions(PDefinitions *p);
  void visitListDef(ListDef *p);
  void visitDef(Def *p); /* abstract class */
  void visitDFunction(DFunction *p);
  void visitDOperator(DOperator *p);
  void visitDHelp(DHelp *p);
  void visitDExpression(DExpression *p);
  void visitCom(Com *p); /* abstract class */
  void visitCComment(CComment *p);
  void visitCEmpty(CEmpty *p);
  void visitListStm(ListStm *p);
  void visitStm(Stm *p); /* abstract class */
  void visitSExpression(SExpression *p);
  void visitSInit(SInit *p);
  void visitSIfElse(SIfElse *p);
  void visitListExp(ListExp *p);
  void visitExp(Exp *p); /* abstract class */
  void visitEDouble(EDouble *p);
  void visitEInteger(EInteger *p);
  void visitEId(EId *p);
  void visitECall(ECall *p);
  void visitEUMinus(EUMinus *p);
  void visitETimes(ETimes *p);
  void visitEDiv(EDiv *p);
  void visitEPlus(EPlus *p);
  void visitEMinus(EMinus *p);
  void visitELt(ELt *p);
  void visitEGt(EGt *p);
  void visitELtEq(ELtEq *p);
  void visitEGtEq(EGtEq *p);
  void visitEEq(EEq *p);
  void visitENEq(ENEq *p);
  void visitEPercentage(EPercentage *p);
  void visitEOperator(EOperator *p);
  void visitListId(ListId *p);

  void visitInteger(Integer i);
  void visitDouble(Double d);
  void visitChar(Char c);
  void visitString(String s);
  void visitIdent(String s);
  void visitId(String s);
 protected:
  char *buf_;
  int cur_, buf_size;

  void inline bufAppend(const char *s)
  {
    int end = cur_ + strlen(s);
    if (end >= buf_size) {
      do buf_size *= 2; /* Double the buffer size */
      while (end >= buf_size);
      resizeBuffer();
    }
    strcpy(&buf_[cur_], s);
    cur_ = end;
  }

  void inline bufAppend(const char c)
  {
    if (cur_ + 1 >= buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    buf_[cur_] = c;
    buf_[++cur_] = 0;
  }

  void inline bufAppend(String str)
  {
    const char *s = str.c_str();
    bufAppend(s);
  }
  void inline bufReset(void)
  {
    if (buf_) free(buf_);
    buf_size = BUFFER_INITIAL;
    buf_ = (char *) malloc(buf_size);
    if (!buf_) {
      fprintf(stderr, "Error: Out of memory while allocating buffer!\n");
      exit(1);
    }
    memset(buf_, 0, buf_size);
    cur_ = 0;
  }

  void inline resizeBuffer(void)
  {
    char *temp = (char *) malloc(buf_size);
    if (!temp)
    {
      fprintf(stderr, "Error: Out of memory while attempting to grow buffer!\n");
      exit(1);
    }
    if (buf_)
    {
      strcpy(temp, buf_);
      free(buf_);
    }
    buf_ = temp;
  }
};



class ShowAbsyn : public Visitor
{
 public:
  ShowAbsyn(void);
  ~ShowAbsyn(void);
  char *show(Visitable *v);

  void visitProgram(Program *p); /* abstract class */
  void visitPDefinitions(PDefinitions *p);
  void visitListDef(ListDef *p);
  void visitDef(Def *p); /* abstract class */
  void visitDFunction(DFunction *p);
  void visitDOperator(DOperator *p);
  void visitDHelp(DHelp *p);
  void visitDExpression(DExpression *p);
  void visitCom(Com *p); /* abstract class */
  void visitCComment(CComment *p);
  void visitCEmpty(CEmpty *p);
  void visitListStm(ListStm *p);
  void visitStm(Stm *p); /* abstract class */
  void visitSExpression(SExpression *p);
  void visitSInit(SInit *p);
  void visitSIfElse(SIfElse *p);
  void visitListExp(ListExp *p);
  void visitExp(Exp *p); /* abstract class */
  void visitEDouble(EDouble *p);
  void visitEInteger(EInteger *p);
  void visitEId(EId *p);
  void visitECall(ECall *p);
  void visitEUMinus(EUMinus *p);
  void visitETimes(ETimes *p);
  void visitEDiv(EDiv *p);
  void visitEPlus(EPlus *p);
  void visitEMinus(EMinus *p);
  void visitELt(ELt *p);
  void visitEGt(EGt *p);
  void visitELtEq(ELtEq *p);
  void visitEGtEq(EGtEq *p);
  void visitEEq(EEq *p);
  void visitENEq(ENEq *p);
  void visitEPercentage(EPercentage *p);
  void visitEOperator(EOperator *p);
  void visitListId(ListId *p);

  void visitInteger(Integer i);
  void visitDouble(Double d);
  void visitChar(Char c);
  void visitString(String s);
  void visitIdent(String s);
  void visitId(String s);
 protected:
  char *buf_;
  int cur_, buf_size;

  void inline bufAppend(const char *s)
  {
    int end = cur_ + strlen(s);
    if (end >= buf_size) {
      do buf_size *= 2; /* Double the buffer size */
      while (end >= buf_size);
      resizeBuffer();
    }
    strcpy(&buf_[cur_], s);
    cur_ = end;
  }

  void inline bufAppend(const char c)
  {
    if (cur_ + 1 >= buf_size)
    {
      buf_size *= 2; /* Double the buffer size */
      resizeBuffer();
    }
    buf_[cur_] = c;
    buf_[++cur_] = 0;
  }

  void inline bufAppend(String str)
  {
    const char *s = str.c_str();
    bufAppend(s);
  }
  void inline bufReset(void)
  {
    if (buf_) free(buf_);
    buf_size = BUFFER_INITIAL;
    buf_ = (char *) malloc(buf_size);
    if (!buf_) {
      fprintf(stderr, "Error: Out of memory while allocating buffer!\n");
      exit(1);
    }
    memset(buf_, 0, buf_size);
    cur_ = 0;
  }

  void inline resizeBuffer(void)
  {
    char *temp = (char *) malloc(buf_size);
    if (!temp)
    {
      fprintf(stderr, "Error: Out of memory while attempting to grow buffer!\n");
      exit(1);
    }
    if (buf_)
    {
      strcpy(temp, buf_);
      free(buf_);
    }
    buf_ = temp;
  }
};




#endif

