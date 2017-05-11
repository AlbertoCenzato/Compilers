%{
#include <ctype.h> 
#include <stdio.h> 

#include "include/fract.h"
#include "include/symbol_table.h"
#include "include/lista.h"
#include "include/code_gen.h"

int yylex();
void yyerror(char *s);

typedef struct fract fract;
Node * head;

%}


%union{

	fract fr;

	int   bool;
	char* str;
 
}

%token <str>  ID
%token <fr>   FRACT
%token <bool> BOOL
%token <str>  KW_FRACT
%token <str>  KW_BOOL
%type  <fr>   expr
%type  <bool> bexpr
%type  <bool> comp

%left '+' '-'
%left '*' '/'
%left OR
%left AND
%right NOT
%nonassoc EQ NE LT GT LE GE

%%

lines : lines expr  '\n'   { printFract($2); }
      | lines bexpr '\n'   { printf("%d\n", $2); }
      | lines comp  '\n'	{ printf("%d\n", $2); }
		| lines declar '\n'  {;}
		| lines assign '\n'  {;}
      | /* empty */
      ;

// TODO: risolvere problema di type checking
expr : expr '+' expr	{ $$ = genFractSum($1,$3); }
     | expr '-' expr	{ $$ = genFractSub($1,$3); }
     | expr '*' expr	{ $$ = genFractMul($1,$3); }
     | expr '/' expr	{ $$ = genFractDiv($1,$3); }
     | '(' expr ')' 	{ $$ = $2; }
     | ID 				{ $$ = getFractVar($1); }	
     | FRACT
     ;

// TODO: risolvere problema di type checking
bexpr : bexpr OR bexpr  { $$ = $1 || $3; }
      | bexpr AND bexpr { if ($1 == 1 && $3 == 1) $$ = 1; 
								  else			  			  $$ = 0; }
      | NOT bexpr 		{ if ($2 == 1 ) $$ = 0; 
								  else          $$ = 1; }
      | '(' bexpr ')'	{ $$ = $2; }
      | comp         	{ $$ = $1; }
      | BOOL
      ;

comp : expr EQ expr { $$ =  ($1.num == $3.num) && ($1.den == $3.den); }
     | expr NE expr { $$ =  ($1.num != $3.num) || ($1.den != $3.den); }
     | expr LT expr { $$ =  fractLT($1,$3); }
     | expr GT expr { $$ =  fractGT($1,$3); }
     | expr LE expr { $$ =  fractLE($1,$3); }
     | expr GE expr { $$ =  fractGE($1,$3); }
     ;
	  
declar : KW_FRACT ID ';' { addFractVar($2);}
       ;
		 
// TODO: risolvere problema di type checking
assign : ID '=' expr  ';' { TAC * tac = malloc(sizeof(TAC));	   
			setFractVar($1, $3);}	 
       ;
%%



