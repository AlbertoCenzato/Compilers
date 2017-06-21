#include "tac.h"

#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 0
#define INITIAL_CAPACITY 64
#define CAPACITY_INCREMENT_RATE 1.7

void** refList = NULL;
int size = INITIAL_SIZE;
int capacity = INITIAL_CAPACITY;

int tacObjects = 0;

struct ThreeAddressCode {
	char* label;
	char* result;
	char* op1;
	char* op;
	char* op2;
};


void expandRefList() {
	capacity *= CAPACITY_INCREMENT_RATE;
	void** newRefList = (void**) malloc(capacity * sizeof(void*));
	for (int i = 0; i < size; i++) {
		newRefList[i] = refList[i];
	}
	for (int i = size; i < capacity; i++) {
		newRefList[i] = NULL;
	}
	free(refList);
	refList = newRefList;
}

/**
 *	\brief Performs a binary search on the reference list
 *	\param ptr: the pointer to look for in the list
 *	\return index of the element or, if not present, the index
 *			  it should have once inserted
 */
int findInRefList(void* ptr) {
	int min = 0;
	int max = size;

	// binary search
	while (min < max) {
		int avrg = (min + max) / 2;
		if (refList[avrg] == ptr)
			return avrg;
		if (refList[avrg] < ptr && refList[avrg] != NULL) {
			min = avrg + 1;
		}
		else {
			max = avrg;
		}
	}

	return min;
}

void insertIntoRefList(void* ptr) {
	
	if (ptr == NULL)	// inserting null pointers is useless and harmful
		return;

	// if refList has reached its maximum capacity expand it
	if (size == capacity) {
		printf("Size == capacity, expanding refList\n");
		expandRefList();
	}

	// if ptr is already present no action needed
	int index = findInRefList(ptr);
	if (refList[index] == ptr)
		return;
	
	// insert ptr keeping refList sorted
	for (int i = size - 1; i >= index; i--) {
		refList[i + 1] = refList[i];
	}
	
	refList[index] = ptr;

	size++;
}

void removeFromRefList(int index) {
	for (int i = index; i < size-1; i++) {
		refList[i] = refList[i + 1];
	}
	size--;
}

void freeString(char* str) {
	int index = findInRefList(str);
	if (refList[index] != str)
		return;
	free(str);
	removeFromRefList(index);
}


TAC* tacAlloc() {
	TAC* tac = (TAC*) malloc(sizeof(TAC));

	tac->label	= NULL;
	tac->result = NULL;
	tac->op1		= NULL;
	tac->op		= NULL;
	tac->op2		= NULL;
	
	if (refList == NULL) {
		refList = (void**) malloc(capacity * sizeof(void*));
		for (int i = 0; i < capacity; i++) {
			refList[i] = NULL;	// intialize to NULL first element to avoid problems when size == 0
		}
	}

	tacObjects++;
	return tac;
}

void tacFree(TAC *tac) {
	if (tac == NULL)
		return;

	freeString(tac->op);
	freeString(tac->op1);
	freeString(tac->op2);
	freeString(tac->result);
	freeString(tac->label);
	
	free(tac);
	tac = NULL;

	tacObjects--;

	if (tacObjects == 0) {
		for (int i = 0; i < size; i++)	// cleans up if any dangling string remained in ref list
			free(refList[i]);
		free(refList);
		refList	= NULL;
		size		= INITIAL_SIZE;
		capacity = INITIAL_CAPACITY;
	}
}

void tacPrint(TAC* tac) {
	if (tac->label != NULL)
		printf("%s: ", tac->label);
	if (tac->result != NULL)
		printf("%s ", tac->result);
	if (tac->result != NULL && tac->op1 != NULL)
		printf("= ");
	if (tac->op1 != NULL)
		printf("%s ", tac->op1);
	if (tac->op != NULL)
		printf("%s ", tac->op);
	if (tac->op2 != NULL)
		printf("%s", tac->op2);
	printf("\n");
}

void tacSetLabel(TAC* tac, char* label) {
	tac->label = label;
	insertIntoRefList(label);
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
	tac->result = res;
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
	return tac->result;
}