/* This Bison file was machine-generated by BNFC */
%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include "ParserError.H"
#include "Absyn.H"

#define YYMAXDEPTH 10000000

typedef struct yy_buffer_state *YY_BUFFER_STATE;
int yyparse(void);
int yylex(void);
YY_BUFFER_STATE yy_scan_string(const char *str);
void yy_delete_buffer(YY_BUFFER_STATE buf);
int yy_mylinenumber;
void initialize_lexer(FILE * inp);
int yywrap(void)
{
  return 1;
}
void yyerror(const char *str)
{
  throw ::parse_error(yy_mylinenumber,str);
}



static Program* YY_RESULT_Program_ = 0;
static ListDef* YY_RESULT_ListDef_ = 0;
static Def* YY_RESULT_Def_ = 0;
static Com* YY_RESULT_Com_ = 0;
static ListStm* YY_RESULT_ListStm_ = 0;
static Stm* YY_RESULT_Stm_ = 0;
static ListExp* YY_RESULT_ListExp_ = 0;
static Exp* YY_RESULT_Exp_ = 0;
static ListId* YY_RESULT_ListId_ = 0;

Program* pProgram(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Program_;
  }
}
Program* pProgram(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Program_;
  }
}

ListDef* pListDef(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListDef_;
  }
}
ListDef* pListDef(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListDef_;
  }
}

Def* pDef(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Def_;
  }
}
Def* pDef(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Def_;
  }
}

Com* pCom(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Com_;
  }
}
Com* pCom(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Com_;
  }
}

ListStm* pListStm(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListStm_;
  }
}
ListStm* pListStm(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_ListStm_;
  }
}

Stm* pStm(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Stm_;
  }
}
Stm* pStm(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Stm_;
  }
}

ListExp* pListExp(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(YY_RESULT_ListExp_->begin(), YY_RESULT_ListExp_->end());
    return YY_RESULT_ListExp_;
  }
}
ListExp* pListExp(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(YY_RESULT_ListExp_->begin(), YY_RESULT_ListExp_->end());
    return YY_RESULT_ListExp_;
  }
}

Exp* pExp15(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}
Exp* pExp15(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}

Exp* pExp14(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}
Exp* pExp14(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}

Exp* pExp13(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}
Exp* pExp13(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}

Exp* pExp12(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}
Exp* pExp12(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}

Exp* pExp11(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}
Exp* pExp11(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}

Exp* pExp9(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}
Exp* pExp9(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}

Exp* pExp8(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}
Exp* pExp8(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}

Exp* pExp7(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}
Exp* pExp7(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}

Exp* pExp3(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}
Exp* pExp3(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}

Exp* pExp(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}
Exp* pExp(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}

Exp* pExp1(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}
Exp* pExp1(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}

Exp* pExp2(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}
Exp* pExp2(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}

Exp* pExp4(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}
Exp* pExp4(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}

Exp* pExp5(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}
Exp* pExp5(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}

Exp* pExp6(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}
Exp* pExp6(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}

Exp* pExp10(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}
Exp* pExp10(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return YY_RESULT_Exp_;
  }
}

ListId* pListId(FILE *inp)
{
  yy_mylinenumber = 1;
  initialize_lexer(inp);
  if (yyparse())
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(YY_RESULT_ListId_->begin(), YY_RESULT_ListId_->end());
    return YY_RESULT_ListId_;
  }
}
ListId* pListId(const char *str)
{
  YY_BUFFER_STATE buf;
  int result;
  yy_mylinenumber = 1;
  initialize_lexer(0);
  buf = yy_scan_string(str);
  result = yyparse();
  yy_delete_buffer(buf);
  if (result)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
std::reverse(YY_RESULT_ListId_->begin(), YY_RESULT_ListId_->end());
    return YY_RESULT_ListId_;
  }
}



%}

%union
{
  int    _int;
  char   _char;
  double _double;
  char*  _string;
  Program* program_;
  ListDef* listdef_;
  Def* def_;
  Com* com_;
  ListStm* liststm_;
  Stm* stm_;
  ListExp* listexp_;
  Exp* exp_;
  ListId* listid_;
}

%token _ERROR_
%token _SYMB_2    //   !
%token _SYMB_16    //   !=
%token _SYMB_5    //   $
%token _SYMB_17    //   %
%token _SYMB_0    //   (
%token _SYMB_1    //   )
%token _SYMB_8    //   *
%token _SYMB_10    //   +
%token _SYMB_3    //   ,
%token _SYMB_7    //   -
%token _SYMB_9    //   /
%token _SYMB_11    //   <
%token _SYMB_13    //   <=
%token _SYMB_6    //   =
%token _SYMB_15    //   ==
%token _SYMB_12    //   >
%token _SYMB_14    //   >=
%token _SYMB_4    //   ?
%token _SYMB_18    //   def
%token _SYMB_19    //   else
%token _SYMB_20    //   if
%token _SYMB_21    //   operator
%token _SYMB_22    //   then
%token<_string> _SYMB_23    //   Id

%type <program_> Program
%type <listdef_> ListDef
%type <def_> Def
%type <com_> Com
%type <liststm_> ListStm
%type <stm_> Stm
%type <listexp_> ListExp
%type <exp_> Exp15
%type <exp_> Exp14
%type <exp_> Exp13
%type <exp_> Exp12
%type <exp_> Exp11
%type <exp_> Exp9
%type <exp_> Exp8
%type <exp_> Exp7
%type <exp_> Exp3
%type <exp_> Exp
%type <exp_> Exp1
%type <exp_> Exp2
%type <exp_> Exp4
%type <exp_> Exp5
%type <exp_> Exp6
%type <exp_> Exp10
%type <listid_> ListId

%start Program
%token<_string> _STRING_
%token<_int>    _INTEGER_
%token<_double> _DOUBLE_

%%
Program : ListDef {  $$ = new PDefinitions($1); YY_RESULT_Program_= $$; }
;
ListDef : /* empty */ {  $$ = new ListDef(); YY_RESULT_ListDef_= $$; }
  | ListDef Def {  $1->push_back($2) ; $$ = $1 ; YY_RESULT_ListDef_= $$; }
;
Def : _SYMB_18 _SYMB_23 _SYMB_0 ListId _SYMB_1 Com ListStm _SYMB_2 Exp {  std::reverse($4->begin(),$4->end()) ;$$ = new DFunction($2, $4, $6, $7, $9); YY_RESULT_Def_= $$; }
  | _SYMB_21 _SYMB_23 _SYMB_0 _SYMB_23 _SYMB_3 _SYMB_23 _SYMB_1 Com ListStm _SYMB_2 Exp {  $$ = new DOperator($2, $4, $6, $8, $9, $11); YY_RESULT_Def_= $$; }
  | _SYMB_4 _STRING_ {  $$ = new DHelp($2); YY_RESULT_Def_= $$; }
  | Exp {  $$ = new DExpression($1); YY_RESULT_Def_= $$; }
;
Com : _STRING_ {  $$ = new CComment($1); YY_RESULT_Com_= $$; }
  | /* empty */ {  $$ = new CEmpty(); YY_RESULT_Com_= $$; }
;
ListStm : /* empty */ {  $$ = new ListStm(); YY_RESULT_ListStm_= $$; }
  | ListStm Stm {  $1->push_back($2) ; $$ = $1 ; YY_RESULT_ListStm_= $$; }
;
Stm : _SYMB_5 Exp {  $$ = new SExpression($2); YY_RESULT_Stm_= $$; }
  | _SYMB_5 _SYMB_23 _SYMB_6 Exp {  $$ = new SInit($2, $4); YY_RESULT_Stm_= $$; }
  | _SYMB_5 _SYMB_20 Exp _SYMB_22 Stm _SYMB_5 _SYMB_19 Stm {  $$ = new SIfElse($3, $5, $8); YY_RESULT_Stm_= $$; }
;
ListExp : /* empty */ {  $$ = new ListExp(); YY_RESULT_ListExp_= $$; }
  | Exp {  $$ = new ListExp() ; $$->push_back($1); YY_RESULT_ListExp_= $$; }
  | Exp _SYMB_3 ListExp {  $3->push_back($1) ; $$ = $3 ; YY_RESULT_ListExp_= $$; }
;
Exp15 : _DOUBLE_ {  $$ = new EDouble($1); YY_RESULT_Exp_= $$; }
  | _INTEGER_ {  $$ = new EInteger($1); YY_RESULT_Exp_= $$; }
  | _SYMB_23 {  $$ = new EId($1); YY_RESULT_Exp_= $$; }
  | _SYMB_0 Exp _SYMB_1 {  $$ = $2; YY_RESULT_Exp_= $$; }
;
Exp14 : _SYMB_23 _SYMB_0 ListExp _SYMB_1 {  std::reverse($3->begin(),$3->end()) ;$$ = new ECall($1, $3); YY_RESULT_Exp_= $$; }
  | Exp15 {  $$ = $1; YY_RESULT_Exp_= $$; }
;
Exp13 : _SYMB_7 Exp13 {  $$ = new EUMinus($2); YY_RESULT_Exp_= $$; }
  | Exp14 {  $$ = $1; YY_RESULT_Exp_= $$; }
;
Exp12 : Exp12 _SYMB_8 Exp13 {  $$ = new ETimes($1, $3); YY_RESULT_Exp_= $$; }
  | Exp12 _SYMB_9 Exp13 {  $$ = new EDiv($1, $3); YY_RESULT_Exp_= $$; }
  | Exp13 {  $$ = $1; YY_RESULT_Exp_= $$; }
;
Exp11 : Exp11 _SYMB_10 Exp12 {  $$ = new EPlus($1, $3); YY_RESULT_Exp_= $$; }
  | Exp11 _SYMB_7 Exp12 {  $$ = new EMinus($1, $3); YY_RESULT_Exp_= $$; }
  | Exp12 {  $$ = $1; YY_RESULT_Exp_= $$; }
;
Exp9 : Exp9 _SYMB_11 Exp10 {  $$ = new ELt($1, $3); YY_RESULT_Exp_= $$; }
  | Exp9 _SYMB_12 Exp10 {  $$ = new EGt($1, $3); YY_RESULT_Exp_= $$; }
  | Exp9 _SYMB_13 Exp10 {  $$ = new ELtEq($1, $3); YY_RESULT_Exp_= $$; }
  | Exp9 _SYMB_14 Exp10 {  $$ = new EGtEq($1, $3); YY_RESULT_Exp_= $$; }
  | Exp10 {  $$ = $1; YY_RESULT_Exp_= $$; }
;
Exp8 : Exp8 _SYMB_15 Exp9 {  $$ = new EEq($1, $3); YY_RESULT_Exp_= $$; }
  | Exp8 _SYMB_16 Exp9 {  $$ = new ENEq($1, $3); YY_RESULT_Exp_= $$; }
  | Exp9 {  $$ = $1; YY_RESULT_Exp_= $$; }
;
Exp7 : Exp7 _SYMB_17 Exp8 {  $$ = new EPercentage($1, $3); YY_RESULT_Exp_= $$; }
  | Exp8 {  $$ = $1; YY_RESULT_Exp_= $$; }
;
Exp3 : Exp3 _SYMB_23 Exp4 {  $$ = new EOperator($1, $2, $3); YY_RESULT_Exp_= $$; }
  | Exp4 {  $$ = $1; YY_RESULT_Exp_= $$; }
;
Exp : Exp1 {  $$ = $1; YY_RESULT_Exp_= $$; }
;
Exp1 : Exp2 {  $$ = $1; YY_RESULT_Exp_= $$; }
;
Exp2 : Exp3 {  $$ = $1; YY_RESULT_Exp_= $$; }
;
Exp4 : Exp5 {  $$ = $1; YY_RESULT_Exp_= $$; }
;
Exp5 : Exp6 {  $$ = $1; YY_RESULT_Exp_= $$; }
;
Exp6 : Exp7 {  $$ = $1; YY_RESULT_Exp_= $$; }
;
Exp10 : Exp11 {  $$ = $1; YY_RESULT_Exp_= $$; }
;
ListId : /* empty */ {  $$ = new ListId(); YY_RESULT_ListId_= $$; }
  | _SYMB_23 {  $$ = new ListId() ; $$->push_back($1); YY_RESULT_ListId_= $$; }
  | _SYMB_23 _SYMB_3 ListId {  $3->push_back($1) ; $$ = $3 ; YY_RESULT_ListId_= $$; }
;

