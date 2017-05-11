#ifndef FRACT_H_
#define FRACT_H_

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

#endif // FRACT_H_
