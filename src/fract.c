#include "fract.h"

#include "node.h"
#include "list.h"
#include "code_gen.h"
#include <stdlib.h>

/*
int mCD(int n1, int n2) {
	if (n2 == 0)
		return n1;
	else
		return mCD(n2, n1%n2);
}

fract  fractSum(fract  fr1, fract  fr2) {
	fract result;
	int den = fr1.den * fr2.den;
	int num = fr1.num*fr2.den + fr2.num*fr1.den;
	int m = mCD(num, den);
	result.num = num / m;
	result.den = den / m;
	return result;
}

fract  fractSub(fract  fr1, fract  fr2) {
	fr2.num = -fr2.num;
	return fractSum(fr1, fr2);
}

fract  fractMul(fract  fr1, fract  fr2) {
	fract  result;
	int num = fr1.num * fr2.num;
	int den = fr1.den * fr2.den;
	int m = mCD(num, den);
	result.num = num / m;
	result.den = den / m;
	return result;
}

fract  fractDiv(fract  fr1, fract fr2) {
	int tmp = fr2.num;
	fr2.num = fr2.den;
	fr2.den = tmp;
	return fractMul(fr1, fr2);
}

int fractLT(fract  f1, fract  f2) {
	return f1.num*f2.den < f2.num*f1.den;
}

int fractGT(fract f1, fract  f2) {
	return f1.num*f2.den > f2.num*f1.den;
}

int fractLE(fract  f1, fract  f2) {
	return f1.num*f2.den <= f2.num*f1.den;
}

int fractGE(fract  f1, fract  f2) {
	return f1.num*f2.den >= f2.num*f1.den;
}

void printFract(fract fr) {
	printf("[%d|%d]", fr.num, fr.den);
}
*/


List* fractGenDecl() {
	List* list = listAlloc();
	listAdd(list, genDecl());
	listAdd(list, genDecl());

	return list;
}

/**
*	Generates three address code instructions for addition
* or subtraction of fract op1 and fract op2.
* @op1: list of instructions for the computation of the first fract.
* @op2: list of instructions for the computation of the second fract.
* @sum: flag stating if the two fracts must be added or subtracted,
*			use 0 for subtraction, everything else for the addition.
*/
List* fractGenSumSub(List* op1, List* op2, int sum) {
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


List* fractGenSum(List* op1, List* op2) {
	return fractGenSumSub(op1, op2, 1);
}

List* fractGenSub(List* op1, List* op2) {
	return fractGenSumSub(op1, op2, 0);
}

List* fractGenMul(List* op1, List* op2) {
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

List* fractGenDiv(List* op1, List* op2) {
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