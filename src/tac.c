#include "tac.h"

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 0
#define INITIAL_CAPACITY 256
#define CAPACITY_INCREMENT_RATE 1.7

char** refList = NULL;
int size = INITIAL_SIZE;
int capacity = INITIAL_CAPACITY;

int tacObjects = 0;

struct ThreeAddressCode {
	char* risul;
	char* op1;
	char* op;
	char* op2;
};


void expandRefList() {
	capacity *= CAPACITY_INCREMENT_RATE;
	char** newRefList = (char**) malloc(capacity * sizeof(char*));
	for (int i = 0; i < size; i++) {
		newRefList[i] = refList[i];
	}
	free(refList);
	refList = newRefList;
}

int findInRefList(char* str) {
	int min = 0;
	int max = size;
	while (min < max) {
		int avrg = (min + max) / 2;
		if (refList[avrg] == str)
			return avrg;
		if (refList[avrg] < str) {
			min = avrg + 1;
		}
		else {
			max = avrg;
		}
	}

	return -1;
}

void insertIntoRefList(char* str) {
	if (size == capacity) {
		printf("Size == capacity, expanding refList\n");
		expandRefList();
	}

	int index;
	for (index = size - 1; index >= 0 && refList[index] < str; index++) {
		refList[index + 1] = refList[index];
	}
	
	refList[index+1] = str;
}

void removeFromRefList(char* str) {
	int index = findInRefList(str);
	if (index == -1)
		return;
	for (int i = index; i < size-1; i++) {
		refList[i] = refList[i + 1];
	}
	size--;
}

int hasBeenFreed(char* str) {
	return findInRefList(str) == -1;
}


TAC* tacAlloc() {
	TAC* tac = (TAC*) malloc(sizeof(TAC));
	
	if (refList == NULL) {
		refList = (char**) malloc(capacity * sizeof(char*));
	}

	tacObjects++;
	return tac;
}

void tacFree(TAC *tac) {
	if (tac == NULL)
		return;

	if (!hasBeenFreed(tac->op)) {
		free(tac->op);
		removeFromRefList(tac->op);
	}
	if (!hasBeenFreed(tac->op1)) {
		free(tac->op1);
		removeFromRefList(tac->op1);
	}
	if (!hasBeenFreed(tac->op2)) {
		free(tac->op2);
		removeFromRefList(tac->op2);
	}
	if (!hasBeenFreed(tac->op2)) {
		free(tac->op2);
		removeFromRefList(tac->op2);
	}
	if (!hasBeenFreed(tac->risul)) {
		free(tac->risul);
		removeFromRefList(tac->risul);
	}

	free(tac);
	tac = NULL;

	tacObjects--;

	if (tacObjects == 0) {
		free(refList);
		refList = NULL;
		size = INITIAL_SIZE;
		capacity = INITIAL_CAPACITY;
	}
}

void tacPrint(TAC* tac) {
	if (tac->risul != NULL)
		printf("%s ", tac->risul);
	if (tac->op1 != NULL)
		printf("= %s ", tac->op1);
	if (tac->op != NULL)
		printf("%s ", tac->op);
	if (tac->op2 != NULL)
		printf("%s", tac->op2);
	printf("\n");
}

void tacSetOp1(TAC* tac, char* op1) {
	tac->op1 = op1;
	insertIntoRefList(op1);
}

void tacSetOp2(TAC* tac, char* op2) {
	tac->op2 = op2;
	insertIntoRefList(op2);
}

void tacSetOper(TAC* tac, char* oper) {
	tac->op = oper;
	insertIntoRefList(oper);
}

void tacSetRes(TAC* tac, char* res) {
	tac->risul = res;
	insertIntoRefList(res);
}

char* tacGetOp1(TAC* tac) {
	return tac->op1;
}

char* tacGetOp2(TAC* tac) {
	return tac->op2;
}

char* tacGetOper(TAC* tac) {
	return tac->op;
}

char* tacGetRes(TAC* tac) {
	return tac->risul;
}