#include "code_gen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

int varCount = 1;

int stringLen(const char* str) {
	int count = -1;
	while (str[++count] != '\0') { }

	return count;
}

/*
char* stringAlloc(const char* str) {
	char* newString = malloc()
}

void stringFree(char* str) {
	
}
*/

char* newVar() {

	// count number of digits of varCount
	int digits = 0;
	for (int tmp = varCount; tmp > 0; tmp = tmp / 10) {
		++digits;
	}

	char* var = (char*) malloc((digits + 2) * sizeof(char));
	sprintf(var, "t%d", varCount);	// sprintf always null terminates the string
	++varCount;
	return var;
}

/**
*	Generates three address code for a generic binary operation
*/
TAC* genOp(char* op1, char* op2, char* operand) {
	TAC *tac = (TAC*) malloc(sizeof(TAC));
	char* result = newVar();
	tac->risul = result;
	tac->op1 = op1;
	tac->op = operand;
	tac->op2 = op2;

	return tac;
}


TAC* genAdd(char* op1, char* op2) {
	char* operand = (char*) malloc(2 * sizeof(char));
	strcpy(operand, "+");
	return genOp(op1, op2, operand);
}


TAC* genSub(char* op1, char* op2) {
	char* operand = (char*) malloc(2 * sizeof(char));
	strcpy(operand, "-");
	return genOp(op1, op2, operand);
}


TAC* genMul(char* op1, char* op2) {
	char* operand = (char*) malloc(2 * sizeof(char));
	strcpy(operand, "*");
	return genOp(op1, op2, operand);
}


TAC* genDiv(char* op1, char* op2) {
	char* operand = (char*) malloc(2 * sizeof(char));
	strcpy(operand, "/");
	return genOp(op1, op2, operand);
}


TAC* genMCD(const char* op1, const char* op2) {
	char* operand = (char*) malloc(3 * sizeof(char));
	strcpy(operand, "MCD");
	return genOp(op1,operand,op2);
}