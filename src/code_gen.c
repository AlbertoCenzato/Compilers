#include "code_gen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tac.h"

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

TAC* genDecl() {
	TAC* tac = tacAlloc();
	tac->risul = newVar();
	return tac;
}

TAC* genAssign(char* val) {
	TAC* tac = tacAlloc();
	tac->risul = newVar();
	tac->op1 = val;

	return tac;
}

/**
*	Generates three address code for a generic binary operation
*/
TAC* genOp(char* op1, char* op2, char* operand) {
	TAC *tac = tacAlloc();
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


TAC* genMCD(char* op1, char* op2) {
	char* operand = (char*) malloc(3 * sizeof(char));
	strcpy(operand, "MCD");
	return genOp(op1,op2, operand);
}


TAC* genEQ(char* op1, char* op2) {
	char* operand = (char*) malloc(3 * sizeof(char));
	strcpy(operand, "==");
	return genOp(op1,operand,op2);
}


TAC* genAND(char* op1, char* op2) {
	char* operand = (char*) malloc(3 * sizeof(char));
	strcpy(operand, "&&");
	return genOp(op1,operand,op2);
}

TAC* genLT(char* op1, char* op2) {
	char* operand = (char*) malloc(3 * sizeof(char));
	strcpy(operand, "<");
	return genOp(op1,operand,op2);
}

TAC* genGT(char* op1, char* op2) {
	char* operand = (char*) malloc(3 * sizeof(char));
	strcpy(operand, ">");
	return genOp(op1,operand,op2);
}


TAC* genLE(char* op1, char* op2) {
	char* operand = (char*) malloc(3 * sizeof(char));
	strcpy(operand, "<=");
	return genOp(op1,operand,op2);
}

TAC* genGE(char* op1, char* op2) {
	char* operand = (char*) malloc(3 * sizeof(char));
	strcpy(operand, ">=");
	return genOp(op1,operand,op2);
}






/*
TAC* gensetFractVar(char* op1, char* op2) {
	char* operand = (char*) malloc(3 * sizeof(char));
	strcpy(operand, "setFractVar");
	return genOp(op1,operand,op2);
	}
*/