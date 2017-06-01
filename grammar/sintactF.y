%{
#include <ctype.h> 
#include <stdio.h> 

int yylex();
void yyerror(char *s);

%}

%code requires {
   #include "fract.h"
   #include "list.h"
   #include "symbol_table.h"
   #include "tac.h"
}

%union{
   Fract fract;
   List * code;
   int   bool;
   char* str;
}

%token <str>   ID
%token <fract> FRACT
%token <bool>  BOOL
%token <str>   KW_FRACT
%token <str>   KW_BOOL
//%type  <code>  lines
%type  <code>  expr
%type  <bool>  bexpr
%type  <bool>  comp
%type <code> assign
%type <code> declar

%left '+' '-'
%left '*' '/'
%left OR
%left AND
%right NOT
%nonassoc EQ NE LT GT LE GE

%%

lines : lines expr  '\n'	{ listPrint($2); }
      //| lines bexpr '\n'	{ printf("%d\n", $2); }
      //| lines comp  '\n'	{ printf("%d\n", $2); }
	  | lines declar '\n'	{ listPrint($2); }
	  | lines assign '\n'	{ ; }
      | /* empty */
      ;

// TODO: risolvere problema di type checking
expr : expr '+' expr	{ $$ = fractGenSum($1,$3); }
     | expr '-' expr	{ $$ = fractGenSub($1,$3); }
     | expr '*' expr	{ $$ = fractGenMul($1,$3); }
     | expr '/' expr	{ $$ = fractGenDiv($1,$3); }
     | '(' expr ')' 	{ $$ = $2; }
     | ID 				{ $$ = fractGenID(getFractVar($1)); }
     | FRACT			{ $$ = fractGenLiteral(&$1); }
     ;

// TODO: risolvere problema di type checking
/*
bexpr : bexpr OR bexpr  { $$ = $1 || $3; }
      | bexpr AND bexpr { if ($1 == 1 && $3 == 1) $$ = 1; 
						  else			  		  $$ = 0; }
      | NOT bexpr 		{ if ($2 == 1 ) $$ = 0; 
						  else          $$ = 1; }
      | '(' bexpr ')'	{ $$ = $2; }
      | comp         	{ $$ = $1; }
      | BOOL
      ;
	  */

	  /*
comp : expr EQ expr { $$ =  ($1.num == $3.num) && ($1.den == $3.den); }
     | expr NE expr { $$ =  ($1.num != $3.num) || ($1.den != $3.den); }
     | expr LT expr { $$ =  fractLT($1,$3); }
     | expr GT expr { $$ =  fractGT($1,$3); }
     | expr LE expr { $$ =  fractLE($1,$3); }
     | expr GE expr { $$ =  fractGE($1,$3); }
     ;
	 */
	  
declar : KW_FRACT ID ';' { List* list = fractGenDecl();
						   addFractVar($2);
						   char* t1 = listGetSecToLast(list)->risul;
						   char* t2 = listGetLast(list)->risul;
						   setFractVar($2, t1, t2); 
						   $$ = list; }
       ;
		 
assign : ID '=' expr  ';' { printf("ID = expr;");
							Fract* fr = getFractVar($1);
							$$ = fractGenAssign(fr, $3); }
       ;
%%

int main() {
	if (yyparse() != 0) 
		fprintf(stderr, "%s\n\n", "Abnormal exit.");

	return 0;
}

