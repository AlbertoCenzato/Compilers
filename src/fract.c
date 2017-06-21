#include "fract.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tac.h"
#include "code_list.h"
#include "code_gen.h"


int mCD(int n1, int n2) {
	if (n2 == 0)
		return n1;
	else
		return mCD(n2, n1%n2);
}

Fract fractLexicalAnalysis(char *text, int len) {

	char *p = text;
	// look for optional sign
	int sign = 0;
	if (*p == '+' | *p == '-') {
		p++;
		sign = 1;
	}

	// get the two number substrings
	char *n1 = ++p;
	while (*p != '|')
		p++;
	*p = '\0';
	char *n2 = ++p;
	text[len - 1] = '\0';

	// convert the substrings into int
	int num = atoi(n1);
	int den = atoi(n2);

	// check if divide by zero. Should be placed in parser
	if (den == 0) {
		printf("Invalid fract! Division by 0 is NAN!\n");
		Fract fract;
		fract.num = NULL;
		fract.den = NULL;
		return fract;
	}

	int m = mCD(num, den);	// reduce num and den

	num = num / m;
	den = den / m;

	int numDigits = 0;
	for (int tmp = num; tmp > 0; tmp = tmp / 10) {
		++numDigits;
	}
	int denDigits = 0;
	for (int tmp = den; tmp > 0; tmp = tmp / 10) {
		++denDigits;
	}

	char* numStr = (char*) malloc((numDigits + 1) * sizeof(char));
	char* denStr = (char*) malloc((denDigits + 1) * sizeof(char));

	sprintf(numStr, "%d", num);
	sprintf(denStr, "%d", den);

	Fract fract;
	fract.num = numStr;
	fract.den = denStr;

	return fract;
}

char* fractNumFromList(CodeList* list) {
	return tacGetRes(listGetSecToLast(list));
}

char* fractDenFromList(CodeList* list) {
	return tacGetRes(listGetLast(list));
}


CodeList* fractGenDecl() {
	CodeList* list = listAlloc();
	listAddBack(list, genDecl());
	listAddBack(list, genDecl());
	
	return list;
}

CodeList* fractGenLiteral(Fract* fract) {
	CodeList* list = listAlloc();
	char* num = strdup(fract->num);
	char* den = strdup(fract->den);

	TAC*  tac = genAssign(num);
	listAddBack(list, tac);
	tac = genAssign(den);
	listAddBack(list, tac);

	return list;
}

CodeList* fractGenID(Fract* fract) {
	CodeList* list = listAlloc();
	
	TAC*  tac = genAssign(fract->num);
	listAddBack(list, tac);
	tac = genAssign(fract->den);
	listAddBack(list, tac);

	return list;
}

// TODO: improve this function
CodeList* fractGenAssign(Fract* fract, CodeList* list) {

	CodeList* newList = listAlloc();

	TAC* tac = tacAlloc();
	tacSetRes(tac, fract->num);
	tacSetOp1(tac, fractNumFromList(list));
	listAddBack(newList, tac);

	tac = tacAlloc();
	tacSetRes(tac, fract->den);
	tacSetOp1(tac, fractDenFromList(list));
	listAddBack(newList, tac);

	listConcat(list, newList);

	return list;
}

/**
 * @brief Generates three address code instructions for addition
 *			or subtraction of fract op1 and fract op2.
 * @op1: list of instructions for the computation of the first fract.
 * @op2: list of instructions for the computation of the second fract.
 * @sum: flag stating if the two fracts must be added or subtracted,
 *			use 0 for subtraction, everything else for the addition.
 */
CodeList* fractGenSumSub(CodeList* op1, CodeList* op2, int sum) {
	char* num1 = fractNumFromList(op1);
	char* den1 = fractDenFromList(op1);
	char* num2 = fractNumFromList(op2);
	char* den2 = fractDenFromList(op2);

	// t1 = num1 * den2
	TAC *tac = genMul(num1, den2);
	char* t1 = tacGetRes(tac);
	CodeList *list = listAlloc();
	listAddBack(list, tac);

	// t2 = num2 * den1
	tac = genMul(num2, den1);
	char* t2 = tacGetRes(tac);
	listAddBack(list, tac);

	// t3 = t1 +- t2
	if (sum != 0)
		tac = genAdd(t1, t2);
	else
		tac = genSub(t1, t2);
	char* t3 = tacGetRes(tac);
	listAddBack(list, tac);

	//  t4 = den1 * den2
	tac = genMul(den1, den2);
	char* t4 = tacGetRes(tac);
	listAddBack(list, tac);

	// t5 = mCD(t3, t4)
	tac = genMCD(t3, t4);
	char* t5 = tacGetRes(tac);
	listAddBack(list, tac);

	// t6 = t3 / t5
	tac = genDiv(t3, t5);
	char* t6 = tacGetRes(tac);
	listAddBack(list, tac);

	//  t7 = t4 / t5
	tac = genDiv(t4, t5);
	char* t7 = tacGetRes(tac);
	listAddBack(list, tac);

	listConcat(op1, op2);
	listConcat(op1, list);

	return op1;
}

CodeList* fractGenSum(CodeList* op1, CodeList* op2) {
	return fractGenSumSub(op1, op2, 1);
}

CodeList* fractGenSub(CodeList* op1, CodeList* op2) {
	return fractGenSumSub(op1, op2, 0);
}

CodeList* fractGenMul(CodeList* op1, CodeList* op2) {
	char* num1 = fractNumFromList(op1);
	char* den1 = fractDenFromList(op1);
	char* num2 = fractNumFromList(op2);
	char* den2 = fractDenFromList(op2);

	// num_ = num1 * num2
	TAC* tac = genMul(num1, num2);
	char* num_ = tacGetRes(tac);
	CodeList* list = listAlloc();
	listAddBack(list, tac);

	// den_ = den1 * den2
	tac = genMul(den1, den2);
	char* den_ = tacGetRes(tac);
	listAddBack(list, tac);

	// m = mCD(num_, den_)
	tac = genMCD(num_, den_);
	char* m = tacGetRes(tac);
	listAddBack(list, tac);

	// num = num_ / m
	tac = genDiv(num_, m);
	char* num = tacGetRes(tac);
	listAddBack(list, tac);

	// den = den_ / m
	tac = genDiv(den_, m);
	char* den = tacGetRes(tac);
	listAddBack(list, tac);

	listConcat(op1, op2);
	listConcat(op1, list);

	return op1;
}

CodeList* fractGenDiv(CodeList* op1, CodeList* op2) {
	char* num1 = fractNumFromList(op1);
	char* den1 = fractDenFromList(op1);
	char* num2 = fractNumFromList(op2);
	char* den2 = fractDenFromList(op2);

	// num_ = num1 * den2
	TAC* tac = genMul(num1, den2);
	char* num_ = tacGetRes(tac);
	CodeList* list = listAlloc();
	listAddBack(list, tac);

	// den_ = den1 * num2
	tac = genMul(den1, num2);
	char* den_ = tacGetRes(tac);
	listAddBack(list, tac);

	// m = mCD(num_, den_)
	tac = genMCD(num_, den_);
	char* m = tacGetRes(tac);
	listAddBack(list, tac);

	// num = num_ / m
	tac = genDiv(num_, m);
	char* num = tacGetRes(tac);
	listAddBack(list, tac);

	// den = den_ / m
	tac = genDiv(den_, m);
	char* den = tacGetRes(tac);
	listAddBack(list, tac);

	listConcat(op1, op2);
	listConcat(op1, list);

	return op1;
}

/**
 * @brief Generates three address code instructions for equality
 *			or ineqality comparison of fract op1 and fract op2.
 *			--! This function assumes the fractions to be minimized !--
 * @op1: list of instructions for the computation of the first fract.
 * @op2: list of instructions for the computation of the second fract.
 * @eq: flag stating if the two fracts must be tested for equality or 
 *		  inequality, use 0 for inequality, everything else for equality.
 */
CodeList* fractGenEQNE(CodeList* op1, CodeList* op2, int eq) {
	char* num1 = fractNumFromList(op1);
	char* den1 = fractDenFromList(op1);
	char* num2 = fractNumFromList(op2);
	char* den2 = fractDenFromList(op2);

	// num_ = num1==num2
	TAC* tac = (eq) ? genEQ(num1, num2) : genNE(num1, num2);
	char* num_ = tacGetRes(tac);
	CodeList* list = listAlloc();
	listAddBack(list, tac);

	// den = den1==den2
	tac = (eq) ? genEQ(den1, den2) : genNE(den1, den2);
	char* den_ = tacGetRes(tac);
	listAddBack(list, tac);

	// resul = num_&&den_
	tac = (eq) ? genAND(num_, den_) : genOR(num_, den_);
	listAddBack(list, tac);

	listConcat(op1, op2);
	listConcat(op1, list);

	return op1;
}

CodeList* fractGenEQ(CodeList* op1, CodeList* op2){
	return fractGenEQNE(op1, op2, 1);
}

CodeList* fractGenNE(CodeList* op1, CodeList* op2){
	return fractGenEQNE(op1, op2, 0);
}

/**
 * @brief Generates three address code instructions for less than,
 *			 greater than, less or equal than, greater or equal than
 *			 comparison of fract op1 and fract op2.
 * @op1: list of instructions for the computation of the first fract.
 * @op2: list of instructions for the computation of the second fract.
 * @eq: flag stating how the two fracts must be compared: 0 for less than,
 *		  1 for greater than, 2 for less than or equal, 3 for greater than 
 *		  or equal.
 */
CodeList* fractGenLTGTLEGE(CodeList* op1, CodeList* op2, int comparision) {
	char* num1 = fractNumFromList(op1);
	char* den1 = fractDenFromList(op1);
	char* num2 = fractNumFromList(op2);
	char* den2 = fractDenFromList(op2);
	CodeList* list = listAlloc();

	// num_1 = num1*den2
	TAC* tac = genMul(num1, den2);
	char* num_1 = tacGetRes(tac);
	listAddBack(list, tac);

	// num_2 = num2*den1
	tac = genMul(num2, den1);
	char* num_2 = tacGetRes(tac);
	listAddBack(list, tac);

	switch (comparision) {
		case 0: tac = genLT(num_1, num_2); break;
		case 1: tac = genGT(num_1, num_2); break;
		case 2: tac = genLE(num_1, num_2); break;
		case 3: tac = genGE(num_1, num_2); break;
	}
	listAddBack(list, tac);

	listConcat(op1, op2);
	listConcat(op1, list);

	return op1;
}

CodeList * fractGenLT(CodeList* op1, CodeList* op2){
	return fractGenLTGTLEGE(op1, op2, 0);
}

CodeList * fractGenGT(CodeList* op1, CodeList* op2){
	return fractGenLTGTLEGE(op1, op2, 1);
}

CodeList * fractGenLE(CodeList* op1, CodeList* op2){
	return fractGenLTGTLEGE(op1, op2, 2);
}

CodeList * fractGenGE(CodeList* op1, CodeList* op2){
	return fractGenLTGTLEGE(op1, op2, 3);
}