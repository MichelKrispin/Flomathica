#ifndef PARSER_HEADER_FILE
#define PARSER_HEADER_FILE

#include<vector>
#include<string>


class Program;
class ListDef;
class Def;
class Com;
class ListStm;
class Stm;
class ListExp;
class Exp;
class ListId;
typedef union
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
} YYSTYPE;

Program* pProgram(FILE *inp);
Program* pProgram(const char *str);
ListDef* pListDef(FILE *inp);
ListDef* pListDef(const char *str);
Def* pDef(FILE *inp);
Def* pDef(const char *str);
Com* pCom(FILE *inp);
Com* pCom(const char *str);
ListStm* pListStm(FILE *inp);
ListStm* pListStm(const char *str);
Stm* pStm(FILE *inp);
Stm* pStm(const char *str);
ListExp* pListExp(FILE *inp);
ListExp* pListExp(const char *str);
Exp* pExp15(FILE *inp);
Exp* pExp15(const char *str);
Exp* pExp14(FILE *inp);
Exp* pExp14(const char *str);
Exp* pExp13(FILE *inp);
Exp* pExp13(const char *str);
Exp* pExp12(FILE *inp);
Exp* pExp12(const char *str);
Exp* pExp11(FILE *inp);
Exp* pExp11(const char *str);
Exp* pExp9(FILE *inp);
Exp* pExp9(const char *str);
Exp* pExp8(FILE *inp);
Exp* pExp8(const char *str);
Exp* pExp7(FILE *inp);
Exp* pExp7(const char *str);
Exp* pExp3(FILE *inp);
Exp* pExp3(const char *str);
Exp* pExp(FILE *inp);
Exp* pExp(const char *str);
Exp* pExp1(FILE *inp);
Exp* pExp1(const char *str);
Exp* pExp2(FILE *inp);
Exp* pExp2(const char *str);
Exp* pExp4(FILE *inp);
Exp* pExp4(const char *str);
Exp* pExp5(FILE *inp);
Exp* pExp5(const char *str);
Exp* pExp6(FILE *inp);
Exp* pExp6(const char *str);
Exp* pExp10(FILE *inp);
Exp* pExp10(const char *str);
ListId* pListId(FILE *inp);
ListId* pListId(const char *str);


#define _ERROR_ 258
#define _SYMB_2 259
#define _SYMB_16 260
#define _SYMB_5 261
#define _SYMB_17 262
#define _SYMB_0 263
#define _SYMB_1 264
#define _SYMB_8 265
#define _SYMB_10 266
#define _SYMB_3 267
#define _SYMB_7 268
#define _SYMB_9 269
#define _SYMB_11 270
#define _SYMB_13 271
#define _SYMB_6 272
#define _SYMB_15 273
#define _SYMB_12 274
#define _SYMB_14 275
#define _SYMB_4 276
#define _SYMB_18 277
#define _SYMB_19 278
#define _SYMB_20 279
#define _SYMB_21 280
#define _SYMB_22 281
#define _SYMB_23 282
#define _STRING_ 283
#define _INTEGER_ 284
#define _DOUBLE_ 285

extern YYSTYPE yylval;

#endif
