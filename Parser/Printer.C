/*** BNFC-Generated Pretty Printer and Abstract Syntax Viewer ***/

#include <string>
#include "Printer.H"
#define INDENT_WIDTH 2


//You may wish to change render
void PrintAbsyn::render(Char c)
{
  if (c == '{')
  {
     bufAppend('\n');
     indent();
     bufAppend(c);
     _n_ = _n_ + INDENT_WIDTH;
     bufAppend('\n');
     indent();
  }
  else if (c == '(' || c == '[')
     bufAppend(c);
  else if (c == ')' || c == ']')
  {
     backup();
     bufAppend(c);
     bufAppend(' ');
  }
  else if (c == '}')
  {
     int t;
     _n_ = _n_ - INDENT_WIDTH;
     for (t=0; t<INDENT_WIDTH; t++) {
       backup();
     }
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == ',')
  {
     backup();
     bufAppend(c);
     bufAppend(' ');
  }
  else if (c == ';')
  {
     backup();
     bufAppend(c);
     bufAppend('\n');
     indent();
  }
  else if (c == ' ') bufAppend(c);
  else if (c == 0) return;
  else
  {
     bufAppend(c);
     bufAppend(' ');
  }
}

void PrintAbsyn::render(String s)
{
  render(s.c_str());
}

bool allIsSpace(const char *s)
{
  char c;
  while ((c = *s++))
    if (! isspace(c)) return false;
  return true;
}

void PrintAbsyn::render(const char *s)
{
  if (*s) /* C string not empty */
  {
    if (allIsSpace(s)) {
      backup();
      bufAppend(s);
    } else {
      bufAppend(s);
      bufAppend(' ');
    }
  }
}

void PrintAbsyn::indent()
{
  int n = _n_;
  while (--n >= 0)
    bufAppend(' ');
}

void PrintAbsyn::backup()
{
  if (buf_[cur_ - 1] == ' ')
    buf_[--cur_] = 0;
}

PrintAbsyn::PrintAbsyn(void)
{
  _i_ = 0; _n_ = 0;
  buf_ = 0;
  bufReset();
}

PrintAbsyn::~PrintAbsyn(void)
{
}

char *PrintAbsyn::print(Visitable *v)
{
  _i_ = 0; _n_ = 0;
  bufReset();
  v->accept(this);
  return buf_;
}

void PrintAbsyn::visitProgram(Program *p) {} //abstract class

void PrintAbsyn::visitPDefinitions(PDefinitions *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  if(p->listdef_) {_i_ = 0; p->listdef_->accept(this);}

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListDef(ListDef *listdef)
{
  for (ListDef::const_iterator i = listdef->begin() ; i != listdef->end() ; ++i)
  {
    (*i)->accept(this);
    render("");
  }
}void PrintAbsyn::visitDef(Def *p) {} //abstract class

void PrintAbsyn::visitDFunction(DFunction *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("def");
  visitId(p->id_);
  render('(');
  if(p->listid_) {_i_ = 0; p->listid_->accept(this);}
  render(')');
  _i_ = 0; p->com_->accept(this);
  if(p->liststm_) {_i_ = 0; p->liststm_->accept(this);}
  render('!');
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitDOperator(DOperator *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render("operator");
  visitId(p->id_1);
  render('(');
  visitId(p->id_2);
  render(',');
  visitId(p->id_3);
  render(')');
  _i_ = 0; p->com_->accept(this);
  if(p->liststm_) {_i_ = 0; p->liststm_->accept(this);}
  render('!');
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitDHelp(DHelp *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('?');
  visitString(p->string_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitDExpression(DExpression *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitCom(Com *p) {} //abstract class

void PrintAbsyn::visitCComment(CComment *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  visitString(p->string_);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitCEmpty(CEmpty *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);


  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListStm(ListStm *liststm)
{
  for (ListStm::const_iterator i = liststm->begin() ; i != liststm->end() ; ++i)
  {
    (*i)->accept(this);
    render("");
  }
}void PrintAbsyn::visitStm(Stm *p) {} //abstract class

void PrintAbsyn::visitSExpression(SExpression *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('$');
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSInit(SInit *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('$');
  visitId(p->id_);
  render('=');
  _i_ = 0; p->exp_->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitSIfElse(SIfElse *p)
{
  int oldi = _i_;
  if (oldi > 0) render(_L_PAREN);

  render('$');
  render("if");
  _i_ = 0; p->exp_->accept(this);
  render("then");
  _i_ = 0; p->stm_1->accept(this);
  render('$');
  render("else");
  _i_ = 0; p->stm_2->accept(this);

  if (oldi > 0) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListExp(ListExp *listexp)
{
  for (ListExp::const_iterator i = listexp->begin() ; i != listexp->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listexp->end() - 1) render(',');
  }
}void PrintAbsyn::visitExp(Exp *p) {} //abstract class

void PrintAbsyn::visitEDouble(EDouble *p)
{
  int oldi = _i_;
  if (oldi > 15) render(_L_PAREN);

  visitDouble(p->double_);

  if (oldi > 15) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEInteger(EInteger *p)
{
  int oldi = _i_;
  if (oldi > 15) render(_L_PAREN);

  visitInteger(p->integer_);

  if (oldi > 15) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEId(EId *p)
{
  int oldi = _i_;
  if (oldi > 15) render(_L_PAREN);

  visitId(p->id_);

  if (oldi > 15) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitECall(ECall *p)
{
  int oldi = _i_;
  if (oldi > 14) render(_L_PAREN);

  visitId(p->id_);
  render('(');
  if(p->listexp_) {_i_ = 0; p->listexp_->accept(this);}
  render(')');

  if (oldi > 14) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEUMinus(EUMinus *p)
{
  int oldi = _i_;
  if (oldi > 13) render(_L_PAREN);

  render('-');
  _i_ = 13; p->exp_->accept(this);

  if (oldi > 13) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitETimes(ETimes *p)
{
  int oldi = _i_;
  if (oldi > 12) render(_L_PAREN);

  _i_ = 12; p->exp_1->accept(this);
  render('*');
  _i_ = 13; p->exp_2->accept(this);

  if (oldi > 12) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEDiv(EDiv *p)
{
  int oldi = _i_;
  if (oldi > 12) render(_L_PAREN);

  _i_ = 12; p->exp_1->accept(this);
  render('/');
  _i_ = 13; p->exp_2->accept(this);

  if (oldi > 12) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEPlus(EPlus *p)
{
  int oldi = _i_;
  if (oldi > 11) render(_L_PAREN);

  _i_ = 11; p->exp_1->accept(this);
  render('+');
  _i_ = 12; p->exp_2->accept(this);

  if (oldi > 11) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEMinus(EMinus *p)
{
  int oldi = _i_;
  if (oldi > 11) render(_L_PAREN);

  _i_ = 11; p->exp_1->accept(this);
  render('-');
  _i_ = 12; p->exp_2->accept(this);

  if (oldi > 11) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitELt(ELt *p)
{
  int oldi = _i_;
  if (oldi > 9) render(_L_PAREN);

  _i_ = 9; p->exp_1->accept(this);
  render('<');
  _i_ = 10; p->exp_2->accept(this);

  if (oldi > 9) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEGt(EGt *p)
{
  int oldi = _i_;
  if (oldi > 9) render(_L_PAREN);

  _i_ = 9; p->exp_1->accept(this);
  render('>');
  _i_ = 10; p->exp_2->accept(this);

  if (oldi > 9) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitELtEq(ELtEq *p)
{
  int oldi = _i_;
  if (oldi > 9) render(_L_PAREN);

  _i_ = 9; p->exp_1->accept(this);
  render("<=");
  _i_ = 10; p->exp_2->accept(this);

  if (oldi > 9) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEGtEq(EGtEq *p)
{
  int oldi = _i_;
  if (oldi > 9) render(_L_PAREN);

  _i_ = 9; p->exp_1->accept(this);
  render(">=");
  _i_ = 10; p->exp_2->accept(this);

  if (oldi > 9) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEEq(EEq *p)
{
  int oldi = _i_;
  if (oldi > 8) render(_L_PAREN);

  _i_ = 8; p->exp_1->accept(this);
  render("==");
  _i_ = 9; p->exp_2->accept(this);

  if (oldi > 8) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitENEq(ENEq *p)
{
  int oldi = _i_;
  if (oldi > 8) render(_L_PAREN);

  _i_ = 8; p->exp_1->accept(this);
  render("!=");
  _i_ = 9; p->exp_2->accept(this);

  if (oldi > 8) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEPercentage(EPercentage *p)
{
  int oldi = _i_;
  if (oldi > 7) render(_L_PAREN);

  _i_ = 7; p->exp_1->accept(this);
  render('%');
  _i_ = 8; p->exp_2->accept(this);

  if (oldi > 7) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitEOperator(EOperator *p)
{
  int oldi = _i_;
  if (oldi > 3) render(_L_PAREN);

  _i_ = 3; p->exp_1->accept(this);
  visitId(p->id_);
  _i_ = 4; p->exp_2->accept(this);

  if (oldi > 3) render(_R_PAREN);

  _i_ = oldi;
}

void PrintAbsyn::visitListId(ListId *listid)
{
  for (ListId::const_iterator i = listid->begin() ; i != listid->end() ; ++i)
  {
    visitId(*i) ;
    if (i != listid->end() - 1) render(',');
  }
}void PrintAbsyn::visitInteger(Integer i)
{
  char tmp[20];
  sprintf(tmp, "%d", i);
  render(tmp);
}

void PrintAbsyn::visitDouble(Double d)
{
  char tmp[24];
  sprintf(tmp, "%.15g", d);
  render(tmp);
}

void PrintAbsyn::visitChar(Char c)
{
  char tmp[4];
  sprintf(tmp, "'%c'", c);
  render(tmp);
}

void PrintAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
  bufAppend(' ');
}

void PrintAbsyn::visitIdent(String s)
{
  render(s);
}

void PrintAbsyn::visitId(String s)
{
  render(s);
}


ShowAbsyn::ShowAbsyn(void)
{
  buf_ = 0;
  bufReset();
}

ShowAbsyn::~ShowAbsyn(void)
{
}

char *ShowAbsyn::show(Visitable *v)
{
  bufReset();
  v->accept(this);
  return buf_;
}

void ShowAbsyn::visitProgram(Program *p) {} //abstract class

void ShowAbsyn::visitPDefinitions(PDefinitions *p)
{
  bufAppend('(');
  bufAppend("PDefinitions");
  bufAppend(' ');
  bufAppend('[');
  if (p->listdef_)  p->listdef_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitListDef(ListDef *listdef)
{
  for (ListDef::const_iterator i = listdef->begin() ; i != listdef->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listdef->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitDef(Def *p) {} //abstract class

void ShowAbsyn::visitDFunction(DFunction *p)
{
  bufAppend('(');
  bufAppend("DFunction");
  bufAppend(' ');
  visitId(p->id_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listid_)  p->listid_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->com_)  p->com_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->liststm_)  p->liststm_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitDOperator(DOperator *p)
{
  bufAppend('(');
  bufAppend("DOperator");
  bufAppend(' ');
  visitId(p->id_1);
  bufAppend(' ');
  visitId(p->id_2);
  bufAppend(' ');
  visitId(p->id_3);
  bufAppend(' ');
  bufAppend('[');
  if (p->com_)  p->com_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->liststm_)  p->liststm_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitDHelp(DHelp *p)
{
  bufAppend('(');
  bufAppend("DHelp");
  bufAppend(' ');
  visitString(p->string_);
  bufAppend(')');
}
void ShowAbsyn::visitDExpression(DExpression *p)
{
  bufAppend('(');
  bufAppend("DExpression");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitCom(Com *p) {} //abstract class

void ShowAbsyn::visitCComment(CComment *p)
{
  bufAppend('(');
  bufAppend("CComment");
  bufAppend(' ');
  visitString(p->string_);
  bufAppend(')');
}
void ShowAbsyn::visitCEmpty(CEmpty *p)
{
  bufAppend("CEmpty");
}
void ShowAbsyn::visitListStm(ListStm *liststm)
{
  for (ListStm::const_iterator i = liststm->begin() ; i != liststm->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != liststm->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitStm(Stm *p) {} //abstract class

void ShowAbsyn::visitSExpression(SExpression *p)
{
  bufAppend('(');
  bufAppend("SExpression");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitSInit(SInit *p)
{
  bufAppend('(');
  bufAppend("SInit");
  bufAppend(' ');
  visitId(p->id_);
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitSIfElse(SIfElse *p)
{
  bufAppend('(');
  bufAppend("SIfElse");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  p->stm_1->accept(this);
  bufAppend(' ');
  p->stm_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitListExp(ListExp *listexp)
{
  for (ListExp::const_iterator i = listexp->begin() ; i != listexp->end() ; ++i)
  {
    (*i)->accept(this);
    if (i != listexp->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitExp(Exp *p) {} //abstract class

void ShowAbsyn::visitEDouble(EDouble *p)
{
  bufAppend('(');
  bufAppend("EDouble");
  bufAppend(' ');
  visitDouble(p->double_);
  bufAppend(')');
}
void ShowAbsyn::visitEInteger(EInteger *p)
{
  bufAppend('(');
  bufAppend("EInteger");
  bufAppend(' ');
  visitInteger(p->integer_);
  bufAppend(')');
}
void ShowAbsyn::visitEId(EId *p)
{
  bufAppend('(');
  bufAppend("EId");
  bufAppend(' ');
  visitId(p->id_);
  bufAppend(')');
}
void ShowAbsyn::visitECall(ECall *p)
{
  bufAppend('(');
  bufAppend("ECall");
  bufAppend(' ');
  visitId(p->id_);
  bufAppend(' ');
  bufAppend('[');
  if (p->listexp_)  p->listexp_->accept(this);
  bufAppend(']');
  bufAppend(' ');
  bufAppend(')');
}
void ShowAbsyn::visitEUMinus(EUMinus *p)
{
  bufAppend('(');
  bufAppend("EUMinus");
  bufAppend(' ');
  bufAppend('[');
  if (p->exp_)  p->exp_->accept(this);
  bufAppend(']');
  bufAppend(')');
}
void ShowAbsyn::visitETimes(ETimes *p)
{
  bufAppend('(');
  bufAppend("ETimes");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEDiv(EDiv *p)
{
  bufAppend('(');
  bufAppend("EDiv");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEPlus(EPlus *p)
{
  bufAppend('(');
  bufAppend("EPlus");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEMinus(EMinus *p)
{
  bufAppend('(');
  bufAppend("EMinus");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitELt(ELt *p)
{
  bufAppend('(');
  bufAppend("ELt");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEGt(EGt *p)
{
  bufAppend('(');
  bufAppend("EGt");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitELtEq(ELtEq *p)
{
  bufAppend('(');
  bufAppend("ELtEq");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEGtEq(EGtEq *p)
{
  bufAppend('(');
  bufAppend("EGtEq");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEEq(EEq *p)
{
  bufAppend('(');
  bufAppend("EEq");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitENEq(ENEq *p)
{
  bufAppend('(');
  bufAppend("ENEq");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEPercentage(EPercentage *p)
{
  bufAppend('(');
  bufAppend("EPercentage");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitEOperator(EOperator *p)
{
  bufAppend('(');
  bufAppend("EOperator");
  bufAppend(' ');
  p->exp_1->accept(this);
  bufAppend(' ');
  visitId(p->id_);
  bufAppend(' ');
  p->exp_2->accept(this);
  bufAppend(')');
}
void ShowAbsyn::visitListId(ListId *listid)
{
  for (ListId::const_iterator i = listid->begin() ; i != listid->end() ; ++i)
  {
    visitId(*i) ;
    if (i != listid->end() - 1) bufAppend(", ");
  }
}

void ShowAbsyn::visitInteger(Integer i)
{
  char tmp[20];
  sprintf(tmp, "%d", i);
  bufAppend(tmp);
}
void ShowAbsyn::visitDouble(Double d)
{
  char tmp[24];
  sprintf(tmp, "%.15g", d);
  bufAppend(tmp);
}
void ShowAbsyn::visitChar(Char c)
{
  bufAppend('\'');
  bufAppend(c);
  bufAppend('\'');
}
void ShowAbsyn::visitString(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}
void ShowAbsyn::visitIdent(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}

void ShowAbsyn::visitId(String s)
{
  bufAppend('\"');
  bufAppend(s);
  bufAppend('\"');
}



