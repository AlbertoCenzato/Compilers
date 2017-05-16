#ifndef FRACT_H_
#define FRACT_H_

/*
struct fract {
	int num;
	int den;
};

typedef struct fract fract;


int mCD(int n1, int n2);

fract  fractSum(fract  fr1, fract  fr2);

fract  fractSub(fract  fr1, fract  fr2);

fract  fractMul(fract  fr1, fract  fr2);

fract  fractDiv(fract  fr1, fract fr2);

int fractLT(fract  f1, fract  f2);

int fractGT(fract f1, fract  f2);

int fractLE(fract  f1, fract  f2);

int fractGE(fract  f1, fract  f2);

void printFract(fract fr);
*/


struct List;
typedef struct List List;

/**
* Generates three address code for the declaration
* of a new fract variable
*/
List* fractGenDecl();

/**
* Generates three address code instructions for addition
* of fract op1 and fract op2.
*/
List* fractGenSum(List* op1, List* op2);

/**
* Generates three address code instructions for subtraction
* of fract op1 and fract op2.
*/
List* fractGenSub(List* op1, List* op2);

/**
* Generates three address code instructions for multiplication
* of fract op1 and fract op2.
*/
List* fractGenMul(List* op1, List* op2);

/**
* Generates three address code instructions for division
* of fract op1 and fract op2.
*/
List* fractGenDiv(List* op1, List* op2);

#endif // FRACT_H_
