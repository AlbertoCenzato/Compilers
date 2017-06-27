#include "backend.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "code_list.h"
#include "tac.h"


int count = 0;
int alreadyDefined(char* c) {
	int n = atoi(c + 1);
	if (n > count) {
		count++;
		return 0;
	}
	return 1;
}


void printDeclaration(char* result, FILE *out) {
	fprintf(out, "int %s;", result);
}

void printAssignment(char* result, char* op1, char* oper, char* op2, FILE *out) {
	if (!alreadyDefined(result))
		fprintf(out, "int ");
	fprintf(out, "%s = ", result);
	if (op1 != NULL)
		fprintf(out, "%s", op1);
	if (oper != NULL)
		fprintf(out, "%s", oper);
	if (op2 != NULL)
		fprintf(out, "%s", op2);
	fprintf(out, ";");
}

void printMcd(char* result, char* op1, char* op2, FILE *out) {
	fprintf(out, "%s = mcd(%s, %s);", result, op1, op2);
}

void printGoto(char* op2, FILE *out) {
	fprintf(out, "goto %s;", op2);
}

void printGotoIfNZ(char* op1, char* op2, FILE *out) {
	fprintf(out, "if (%s != 0) goto %s;", op1, op2);
}

void bkndPrintTac(TAC* tac, FILE* out) {
	char* label  = tacGetLabel(tac);
	char* result =	tacGetRes  (tac);
	char* op1	 =	tacGetOp1  (tac);
	char* oper	 =	tacGetOper (tac);
	char* op2	 =	tacGetOp2  (tac);

	if (label != NULL) {
		if (!alreadyDefined(result)) {
			fprintf(out, "int %s;\n", result);
		}
		fprintf(out, "%s: ", label);
	}

	if (oper != NULL) {
		if (strcmp(oper, GEN_MCD) == 0)
			printMcd(result, op1, op2, out);
		else if (strcmp(oper, GEN_GOTO) == 0)
			printGoto(op2, out);
		else if (strcmp(oper, GEN_GOTOIFNZ) == 0)
			printGotoIfNZ(op1, op2, out);
		else
			printAssignment(result, op1, oper, op2, out);
	}
	else if(op1 == NULL && op2 == NULL && oper == NULL)
		printDeclaration(result, out);
	else
		printAssignment(result, op1, oper, op2, out);

	fprintf(out, "\n");
}

/**
 *	\brief WARNING! by now this is a destructive call. 
 *			 The list is printed and deallocated
 */
void bkndPrintToC(CodeList* code, FILE *out) {
	
	while(listHasNext(code)) {
		TAC* tac = listGetNext(code);
		bkndPrintTac(tac, out);
	}
	listFree(code);
}