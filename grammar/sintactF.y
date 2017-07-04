%{
#include <ctype.h> 
#include <stdio.h>

extern FILE* yyin;
extern FILE* yyout;

int yylex();
void yyerror(char *s);

int lineCount = 0;

%}

%code requires {
   #include "fract.h"
	#include "bool.h"
   #include "code_list.h"
	#include "ctrl_flow.h"
	#include "backend.h"
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

program : block END_OF_FILE { listPrint($1);
										bkndPrintToC($1, yyout); 
										return 0; }

block : block statement		{ ctrlBackpatch($1, $2);
									  $$ = listConcat($1, $2); }
		| block error ';'		{ printf("statement error at line %d!\n", lineCount); yyerrok; $$ = $1;  }
		| statement				{ $$ = $1; }
		| error ';'				{ printf("statement error at line %d!\n", lineCount); yyerrok; $$ = listAlloc(); }
		;

statement : WHILE '(' bexpr ')' '{' block '}'							{ $$ = ctrlGenWhile($3,$6); }
			 | IF	   '(' bexpr ')' '{' block '}'							{ $$ = ctrlGenIf($3, $6); }

			 | IF		'(' bexpr ')' '{' block '}' ELSE '{' block '}'	{ $$ = ctrlGenIfElse($3,$6,$10); }
			 | declar																{ $$ = $1; }
			 | assign																{ $$ = $1; }
			 | WHILE error '}'	{ printf("while error at line %d!\n", lineCount); yyerrok; $$ = listAlloc();  }
			 | IF error '}'		{ printf("if error at line %d!\n", lineCount); yyerrok; $$ = listAlloc();  }
			 ;

expr : expr '+' expr	{ $$ = fractGenSum($1,$3); }
     | expr '-' expr	{ $$ = fractGenSub($1,$3); }
     | expr '*' expr	{ $$ = fractGenMul($1,$3); }
     | expr '/' expr	{ $$ = fractGenDiv($1,$3); }
     | '(' expr ')' 	{ $$ = $2; }
     | ID 				{ $$ = fractGenID($1); }
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
	  
declar : KW_FRACT ID ';' { $$ = fractGenDecl($2); }
       ;
		 
assign : ID '=' expr  ';' { $$ = fractGenAssign($1, $3); }
       ;

%%

int main(int argc, char **argv) {

	if (argc < 2) {
		printf("Wrong arguments number!\n");
		printf("Usage: f_compiler input_f_file [output_c_file]\n");
		return 0;
	}

	yyin = fopen(argv[1], "r");

	if (argc > 2) {
		yyout = fopen(argv[2], "w");
	}

	if (yyparse() != 0) 
		fprintf(stderr, "%s\n\n", "Abnormal exit.");

	return 0;
}