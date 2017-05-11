#include "../include/fract.h"

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