%{
#include <ctype.h> 
#include <stdio.h> 

int yylex();
void yyerror(char *s);

%}

%code requires {
	#include "code_gen.h"
   #include "fract.h"
	#include "bool.h"
   #include "code_list.h"
   #include "symbol_table.h"
   #include "tac.h"
	#include "ctrl_flow.h"
}

%union{
   Fract fract;
   CodeList * code;
   int   bool;
   char* str;
}

%token <str>   ID
%token <fract> FRACT
%token <bool>  BOOL
%token <str>   KW_FRACT
%token <str>   KW_BOOL
%token <str>   IF
%token <str>   ELSE
%token <str>   WHILE
%token <str>	END_OF_FILE

//%type  <code>  lines
%type <code> expr
%type <code> bexpr
%type <code> comp
%type <code> assign
%type <code> declar
%type <code> block
%type <code> statement
%type <code> program

%left '+' '-'
%left '*' '/'
%left OR
%left AND
%right NOT
%nonassoc EQ NE LT GT LE GE

%%

program : block END_OF_FILE { listPrint($1); }

block : block statement	{ ctrlBackpatch($1, $2);
								  $$ = listConcat($1, $2); }
		| statement			{ $$ = $1; }
		;

statement : WHILE '(' bexpr ')' '{' block '}'							{ }
			 | IF	   '(' bexpr ')' '{' block '}'							{ $$ = ctrlGenIf($3, $6); }

			 | IF		'(' bexpr ')' '{' block '}' ELSE '{' block '}'	{ }
			 | declar																{ $$ = $1; }
			 | assign																{ $$ = $1; }
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

bexpr : bexpr OR bexpr  { $$ = boolGenOR ($1,$3); }
      | bexpr AND bexpr { $$ = boolGenAND($1,$3); }
      | NOT bexpr 		{ $$ = boolGenNOT($2); }
      | '(' bexpr ')'	{ $$ = $2; }
      | comp         	{ $$ = $1; }
      //| BOOL
      ;

comp : expr EQ expr { $$ = fractGenEQ($1,$3); }
     | expr NE expr { $$ = fractGenNE($1,$3); }
     | expr LT expr { $$ = fractGenLT($1,$3); }
     | expr GT expr { $$ = fractGenGT($1,$3); }
     | expr LE expr { $$ = fractGenLE($1,$3); }
     | expr GE expr { $$ = fractGenGE($1,$3); }
     ;
	  
// TODO: collapse this in a single function call
declar : KW_FRACT ID ';' { CodeList* list = fractGenDecl();
									addFractVar($2, NULL, NULL);
									char* t1 = tacGetRes(listGetSecToLast(list));
									char* t2 = tacGetRes(listGetLast(list));
									setFractVar($2, t1, t2); 
									$$ = list; }
       ;
		 
assign : ID '=' expr  ';' { Fract* fr = getFractVar($1);
									 $$ = fractGenAssign(fr, $3); }
       ;
%%

int main() {
	if (yyparse() != 0) 
		fprintf(stderr, "%s\n\n", "Abnormal exit.");

	return 0;
}