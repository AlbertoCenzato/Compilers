#include "fract.h"

#include <string.h>
#include <stdio.h>

#include "tac.h"
#include "list.h"
#include "code_gen.h"


char* fractNumFromList(List* list) {
	return listGetSecToLast(list)->risul;
}

char* fractDenFromList(List* list) {
	return listGetLast(list)->risul;
}


List* fractGenDecl() {
	List* list = listAlloc();
	listAdd(list, genDecl());
	listAdd(list, genDecl());
	
	return list;
}

List* fractGenLiteral(Fract* fract) {
	List* list = listAlloc();
	char* num = strdup(fract->num);
	char* den = strdup(fract->den);

	TAC*  tac = genAssign(num);
	listAdd(list, tac);
	tac = genAssign(den);
	listAdd(list, tac);

	return list;
}

List* fractGenID(Fract* fract) {
	List* list = listAlloc();
	
	TAC*  tac = genAssign(fract->num);
	listAdd(list, tac);
	tac = genAssign(fract->den);
	listAdd(list, tac);

	return list;
}

// TODO: improve this function
List* fractGenAssign(Fract* fract, List* list) {

	List* newList = listAlloc();

	TAC* tac = tacAlloc();
	tac->risul = fract->num;
	tac->op1 = fractNumFromList(list);
	listAdd(newList, tac);

	tac = tacAlloc();
	tac->risul = fract->den;
	tac->op1 = fractDenFromList(list);
	listAdd(newList, tac);

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
List* fractGenSumSub(List* op1, List* op2, int sum) {
	char* num1 = listGetSecToLast(op1)->risul;
	char* den1 = listGetLast(op1)->risul;
	char* num2 = listGetSecToLast(op2)->risul;
	char* den2 = listGetLast(op2)->risul;

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
	char* num1 = listGetSecToLast(op1)->risul;
	char* den1 = listGetLast(op1)->risul;
	char* num2 = listGetSecToLast(op2)->risul;
	char* den2 = listGetLast(op2)->risul;

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
	char* num1 = listGetSecToLast(op1)->risul;
	char* den1 = listGetLast(op1)->risul;
	char* num2 = listGetSecToLast(op2)->risul;
	char* den2 = listGetLast(op2)->risul;

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

List * fractGenEQ(List* op1, List* op2){

    char* num1 = listGetSecToLast(op1)->risul;
	char* den1 = listGetLast(op1)->risul;
	char* num2 = listGetSecToLast(op2)->risul;
	char* den2 = listGetLast(op2)->risul;

    //num_=num1==num2
    TAC* tac = genEQ(num1, num2);
    char* num_ = tac->risul;
    List* list = listAlloc();
    listAdd(list, tac);


    //den=den1==den2
    tac = genEQ(den1, den2);
    char* den_ = tac->risul;
    listAdd(list, tac);


    //resul=num_&&den_
    tac = genAND(num_, den_);
    listAdd(list, tac);

    listConcat(op1, op2);
    listConcat(op1, list);
    //TODO free

    return op1;
}



List * fractGenNE(List* op1, List* op2){

  List * NE=fractGenEQ(op1,op2);
  listGeLast(NE)->op='!=';
  return NE;
}



List * fractGenLT(List* op1, List* op2){

    char* num1 = listGetSecToLast(op1)->risul;
	char* den1 = listGetLast(op1)->risul;
	char* num2 = listGetSecToLast(op2)->risul;
	char* den2 = listGetLast(op2)->risul;

    //num_1=den2*num1
    TAC* tac = genMul(num1, den2);
    tac = genMul(den2, den1);
    char* num _1= tac->risul;
    listAdd(list, tac);

    //num_2=den1*num2
    tac = genMul(den1, num2);
    char* num_2 = tac->risul;
    listAdd(list, tac);

    //risul=num_2>num_1
    tac = genGT(num_2, num_1);
    listAdd(list, tac);


    listConcat(op1, op2);
    listConcat(op1, list);

    return op1;
}


List * fractGenGT(List* op1, List* op2){

    char* num1 = listGetSecToLast(op1)->risul;
	char* den1 = listGetLast(op1)->risul;
	char* num2 = listGetSecToLast(op2)->risul;
	char* den2 = listGetLast(op2)->risul;

    //num_1=den2*num1
    TAC* tac = genMul(num1, den2);
    tac = genMul(den2, den1);
    char* num_1 = tac->risul;
    listAdd(list, tac);

    //num_2=den1*num2
    tac = genMul(den1, num2);
    char* num_2 = tac->risul;
    listAdd(list, tac);

    //risul=num_2<num_1
    tac = genLT(num_2,num_1);
    listAdd(list, tac);


    listConcat(op1, op2);
    listConcat(op1, list);

    return op1;
}

List * fractGenLE(List* op1, List* op2){

  List * NE=fractGenEQ(op1,op2);
  listGeLast(NE)->op='>=';
  return NE;
}

List * fractGenGE(List* op1, List* op2){

  List * NE=fractGenEQ(op1,op2);
  listGeLast(NE)->op='<=';
  return NE;
}




//new method for updating symboltable
/*
setFractVar(char * id, List * expr){
char* num = listGetSecToLast(expr)->risul;
char* den = listGetLast(expr)->risul;



//t1 = setFractVar(id,num)
TAC * tac = gensetNumVar(id,num);
	listAdd(expr, tac);


//t2 = setFratVar(id, den)
tac = gensetDenVar(id,den);
	listAdd(expr, tac);

}
*/
