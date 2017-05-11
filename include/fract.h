#ifndef FRACT_H_
#define FRACT_H_

struct fract {
	int num;
	int den;
};


int mCD(int n1, int n2) {
    if (n2==0)
        return n1;
    else
        return mCD(n2, n1%n2);
}

struct fract  fractSum(struct fract  fr1, struct fract  fr2) {
	struct fract result;
	int den = fr1.den * fr2.den;
	int num = fr1.num*fr2.den + fr2.num*fr1.den;
	int m = mCD(num, den);
	result.num = num / m;
	result.den = den / m;
	return result;
}

struct fract  fractSub(struct fract  fr1, struct fract  fr2) {
	fr2.num = -fr2.num;
	return fractSum(fr1,fr2);
}

struct fract  fractMul(struct fract  fr1, struct fract  fr2) {
	struct fract  result;
	int num = fr1.num * fr2.num;
	int den = fr1.den * fr2.den;
	int m = mCD(num, den);
	result.num = num / m;
	result.den = den / m;
	return result;
}

struct fract  fractDiv(struct fract  fr1, struct fract fr2) {
	int tmp = fr2.num;
	fr2.num = fr2.den;
	fr2.den = tmp;
	return fractMul(fr1,fr2);
}

int fractLT(struct fract  f1, struct fract  f2) {
	return f1.num*f2.den < f2.num*f1.den;
}

int fractGT(struct fract f1, struct fract  f2) {
	return f1.num*f2.den > f2.num*f1.den;
}

int fractLE(struct fract  f1, struct fract  f2) {
	return f1.num*f2.den <= f2.num*f1.den;
}

int fractGE(struct fract  f1, struct fract  f2) {
	return f1.num*f2.den >= f2.num*f1.den;
}

void printFract(struct fract fr) {
	printf("[%d|%d]",fr.num,fr.den);
}

#endif
