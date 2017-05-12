#include "../include/code_gen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/node.h"

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

/**
*	Generates three address code instructions for addition
* or subtraction of fract op1 and fract op2.
* @op1: list of instructions for the computation of the first fract.
* @op2: list of instructions for the computation of the second fract.
* @sum: flag stating if the two fracts must be added or subtracted,
*			use 0 for subtraction, everything else for the addition.
*/
List* genFractSumSub(List* op1, List* op2, int sum) {
	char* num1 = listFindSecToLast(op1)->val->risul;
	char* den1 = listFindLast(op1)->val->risul;
	char* num2 = listFindSecToLast(op2)->val->risul;
	char* den2 = listFindLast(op2)->val->risul;

	// t1 = num1 * den2
	TAC *tac = genMul(num1, den2);
	char* t1 = tac->risul;
	List *list = listAlloc();
	listAdd(list, tac);

	// t2 = num2 * den1
	tac = genMul(num2, den1);
	char* t2 = tac->risul;
	listAdd(list, tac);

	// t3 = t1 +- t2
	if (sum != 0)
		tac = genAdd(t1, t2);
	else
		tac = genSub(t1, t2);
	char* t3 = tac->risul;
	listAdd(list, tac);

	//  t4 = den1 * den2
	tac = genMul(den1, den2);
	char* t4 = tac->risul;
	listAdd(list, tac);

	// t5 = mCD(t3, t4)
	tac = genMCD(t3, t4);
	char* t5 = tac->risul;
	listAdd(list, tac);

	// t6 = t3 / t5
	tac = genDiv(t3, t5);
	char* t6 = tac->risul;
	listAdd(list, tac);

	//  t7 = t4 / t5
	tac = genDiv(t4, t5);
	char* t7 = tac->risul;
	listAdd(list, tac);

	listConcat(op1, op2);
	listConcat(op1, list);

	return op1;
}


List* genFractSum(List* op1, List* op2) {
	return genFractSumSub(op1, op2, 1);
}

List* genFractSub(List* op1, List* op2) {
	return genFractSumSub(op1, op2, 0);
}

List* genFractMul(List* op1, List* op2) {
	char* num1 = listFindSecToLast(op1)->val->risul;
	char* den1 = listFindLast(op1)->val->risul;
	char* num2 = listFindSecToLast(op2)->val->risul;
	char* den2 = listFindLast(op2)->val->risul;

	// num_ = num1 * num2
	TAC* tac = genMul(num1, num2);
	char* num_ = tac->risul;
	List* list = listAlloc();
	listAdd(list, tac);

	// den_ = den1 * den2
	tac = genMul(den1, den2);
	char* den_ = tac->risul;
	listAdd(list, tac);

	// m = mCD(num_, den_)
	tac = genMCD(num_, den_);
	char* m = tac->risul;
	listAdd(list, tac);

	// num = num_ / m
	tac = genDiv(num_, m);
	char* num = tac->risul;
	listAdd(list, tac);

	// den = den_ / m
	tac = genDiv(den_, m);
	char* den = tac->risul;
	listAdd(list, tac);

	listConcat(op1, op2);
	listConcat(op1, list);

	return op1;
}

List* genFractDiv(List* op1, List* op2) {
	char* num1 = listFindSecToLast(op1)->val->risul;
	char* den1 = listFindLast(op1)->val->risul;
	char* num2 = listFindSecToLast(op2)->val->risul;
	char* den2 = listFindLast(op2)->val->risul;

	// num_ = num1 * den2
	TAC* tac = genMul(num1, den2);
	char* num_ = tac->risul;
	List* list = listAlloc();
	listAdd(list, tac);

	// den_ = den1 * num2
	tac = genMul(den1, num2);
	char* den_ = tac->risul;
	listAdd(list, tac);

	// m = mCD(num_, den_)
	tac = genMCD(num_, den_);
	char* m = tac->risul;
	listAdd(list, tac);

	// num = num_ / m
	tac = genDiv(num_, m);
	char* num = tac->risul;
	listAdd(list, tac);

	// den = den_ / m
	tac = genDiv(den_, m);
	char* den = tac->risul;
	listAdd(list, tac);

	listConcat(op1, op2);
	listConcat(op1, list);

	return op1;
}
