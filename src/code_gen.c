#include "code_gen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tac.h"

int varCount	= 1;
int labelCount = 1;

int stringLen(const char* str) {
	int count = -1;
	while (str[++count] != '\0') { }

	return count;
}

char* newTmpVariable() {

	// count number of digits of varCount
	int digits = 0;
	for (int tmp = varCount; tmp > 0; tmp = tmp / 10) {
		digits++;
	}

	char* var = (char*) malloc((digits + 2) * sizeof(char));
	sprintf(var, "t%d", varCount);	// sprintf always null terminates the string
	varCount++;
	return var;
}

char* genNewLabel() {
	// count number of digits of labelCount
	int digits = 0;
	for (int tmp = labelCount; tmp > 0; tmp = tmp / 10) {
		digits++;
	}

	char* label = (char*) malloc((digits + 2) * sizeof(char));
	sprintf(label, "t%d", labelCount);	// sprintf always null terminates the string
	labelCount++;
	return label;
}

TAC* genDecl() {
	TAC* tac = tacAlloc();
	tacSetRes(tac, newTmpVariable());
	return tac;
}

TAC* genAssign(char* val) {
	TAC* tac = tacAlloc();
	tacSetRes(tac, newTmpVariable());
	tacSetOp1(tac, val);
	
	return tac;
}

/**
 *	@brief Generates three address code for a generic binary operation
 */
TAC* genBinaryOp(char* op1, char* oper, char* op2) {
	TAC *tac = tacAlloc();
	char* result = newTmpVariable();
	tacSetRes(tac, result);
	tacSetOp1(tac, op1);
	tacSetOper(tac, oper);
	tacSetOp2(tac, op2);

	return tac;
}

/**
 *	@brief Generates three address code for a generic unary operation
 */
TAC* genUnaryOp(char* op1, char* oper) {
	TAC *tac = tacAlloc();
	char* result = newTmpVariable();
	tacSetRes(tac, result);
	tacSetOper(tac, oper);
	tacSetOp2(tac, op1);

	return tac;
}

// ---------- arithmetic operatoins ----------

TAC* genAdd(char* op1, char* op2) {
	char* oper = (char*) malloc(2 * sizeof(char));
	strcpy(oper, GEN_ADD);
	return genBinaryOp(op1, oper, op2);
}


TAC* genSub(char* op1, char* op2) {
	char* oper = (char*) malloc(2 * sizeof(char));
	strcpy(oper, GEN_SUB);
	return genBinaryOp(op1, oper, op2);
}


TAC* genMul(char* op1, char* op2) {
	char* oper = (char*) malloc(2 * sizeof(char));
	strcpy(oper, GEN_MUL);
	return genBinaryOp(op1, oper, op2);
}


TAC* genDiv(char* op1, char* op2) {
	char* oper = (char*) malloc(2 * sizeof(char));
	strcpy(oper, GEN_DIV);
	return genBinaryOp(op1, oper, op2);
}


TAC* genMCD(char* op1, char* op2) {
	char* oper = (char*) malloc(3 * sizeof(char));
	strcpy(oper, GEN_MCD);
	return genBinaryOp(op1, oper, op2);
}

// ---------- relational operations ----------

TAC* genEQ(char* op1, char* op2) {
	char* oper = (char*) malloc(3 * sizeof(char));
	strcpy(oper, GEN_EQ);
	return genBinaryOp(op1, oper, op2);
}

TAC* genNE(char* op1, char* op2) {
	char* oper = (char*) malloc(3 * sizeof(char));
	strcpy(oper, GEN_NE);
	return genBinaryOp(op1, oper, op2);
}

TAC* genLT(char* op1, char* op2) {
	char* oper = (char*) malloc(3 * sizeof(char));
	strcpy(oper, GEN_LT);
	return genBinaryOp(op1, oper, op2);
}

TAC* genGT(char* op1, char* op2) {
	char* oper = (char*) malloc(3 * sizeof(char));
	strcpy(oper, GEN_GT);
	return genBinaryOp(op1, oper, op2);
}

TAC* genLE(char* op1, char* op2) {
	char* oper = (char*) malloc(3 * sizeof(char));
	strcpy(oper, GEN_LE);
	return genBinaryOp(op1, oper, op2);
}

TAC* genGE(char* op1, char* op2) {
	char* oper = (char*) malloc(3 * sizeof(char));
	strcpy(oper, GEN_GE);
	return genBinaryOp(op1, oper, op2);
}


// ---------- logical operations ----------

TAC* genAND(char* op1, char* op2) {
	char* oper = (char*) malloc(3 * sizeof(char));
	strcpy(oper, GEN_AND);
	return genBinaryOp(op1, oper, op2);
}

TAC* genOR(char* op1, char* op2) {
	char* oper = (char*) malloc(3 * sizeof(char));
	strcpy(oper, GEN_OR);
	return genBinaryOp(op1, oper, op2);
}

TAC* genNOT(char* op1) {
	char* oper = (char*) malloc(2 * sizeof(char));
	strcpy(oper, GEN_NOT);
	return genUnaryOp(op1, oper);
}


TAC* genGoto(char* label) {
	TAC* tac = tacAlloc();
	tacSetOp2(tac, label);
	char* oper = (char*) malloc(5 * sizeof(char));
	strcpy(oper, GEN_GOTO);
	tacSetOper(tac, oper);

	return tac;
}

TAC* genConditionalGoto(char* op1, char* op2) {
	TAC* tac = tacAlloc();
	tacSetOp1(tac,op1);
	tacSetOp2(tac, op2);
	char* oper = (char*) malloc(8 * sizeof(char));
	strcpy(oper, GEN_GOTOIFZ);
	tacSetOper(tac, oper);

	return tac;
}