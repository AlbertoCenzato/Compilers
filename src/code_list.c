#include "code_list.h"

#include <stdlib.h>
#include <stdio.h>

#include "tac.h"
#include "code_gen.h"

// ---------- Node private inner class ----------

struct Node {
	TAC* val;
	struct Node* next;
};

typedef struct Node Node;

Node* nodeAlloc(TAC* tac) {
	Node* newNode = (Node*) malloc(sizeof(Node));
	newNode->val = tac;
	//new->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

void nodeFree(Node *node) {
	if (node == NULL)
		return;
	tacFree(node->val);
	free(node);
	node = NULL;
}


// -------------------------------------------
// ---------------- CodeList -----------------
// -------------------------------------------

struct CodeList {
	Node* head;
	Node* secToLast;
	CodeList* nextlist;
	int length;
};

CodeList* listAlloc() {
	CodeList *newList = (CodeList*) malloc(sizeof(CodeList));
	newList->head = NULL;
	newList->secToLast = NULL;
	newList->nextlist = NULL;
	newList->length = 0;

	return newList;
}

void listFree(CodeList *list) {
	if (list == NULL)
		return;

	Node *next = list->head;
	while (next != NULL) {
		Node *prev = next;
		next = next->next;
		nodeFree(prev);
	}

	listFree(list->nextlist);
	free(list);

	list = NULL;
}


int listLength(CodeList *list) {
	return list->length;
}

int listIsEmpty(CodeList *list) {
	return list->length == 0;
}

TAC* listGetFirst(CodeList* list) {
	return list->head->val;
}

TAC* listGetLast(CodeList* list) {
	if (list->length > 1)
		return list->secToLast->next->val;
	if (list->length == 1)
		return list->head->val;
	return NULL;	
}

TAC* listGetSecToLast(CodeList* list) {
	if (list->length > 1)
		return list->secToLast->val;
	return NULL;
}

void listAddBack(CodeList *list, TAC *tac) {

	Node *newNode = nodeAlloc(tac);

	if (list->length > 1) {
		Node *last = list->secToLast->next;
		last->next = newNode;
		list->secToLast = last;
	}
	else if (list->length == 1) {
		list->head->next = newNode;
		list->secToLast = list->head;
	}
	else {
		list->head = newNode;
	}

	list->length++;
}

TAC* listPopFront(CodeList* codeList) {
	if (codeList->length < 1)
		return NULL;

	TAC* tac = codeList->head->val;
	if (codeList->secToLast == codeList->head)
		codeList->secToLast = NULL;
	free(codeList->head);	// frees the node, not the Three Address Code it contains
	codeList->head = codeList->head->next;
	codeList->length--;

	return tac;
}

CodeList* listConcat(CodeList* list1, CodeList* list2) {

	if (list1 == NULL) {
		list1 = list2;
		list2 = NULL;
		return list1;
	}

	if (list2 == NULL)
		return list1;

	listConcat(list1->nextlist, list2->nextlist);

	if (list1->length == 0) {
		listFree(list1);
		list1 = list2;
		list2 = NULL;
	}
	else {
		if (list1->length > 1) {
			Node *last = list1->secToLast->next;
			last->next = list2->head;
			if (list2->length > 1)
				list1->secToLast = list2->secToLast;
			else if (list2->length == 1)
				list1->secToLast = list1->secToLast->next;
			// if list2->length == 0 no action needed
			list1->length += list2->length;
		}
		else if (list1->length == 1) {
			list1->head->next = list2->head;
			if (list2->length > 1)
				list1->secToLast = list2->secToLast;
			else if (list2->length == 1)
				list1->secToLast = list1->head;
			// if list2->length == 0 no action needed
			list1->length += list2->length;
		}

		free(list2);
		list2 = NULL;
	}

	return list1;
}

void listAddToNextList(CodeList* codeList, TAC* tac) {
	listAddBack(codeList->nextlist, tac);
}

CodeList* listGetNextList(CodeList* codeList) {
	return codeList->nextlist;
}

void listPrint(CodeList* list) {
	Node* node = list->head;
	while(node != NULL) {
		tacPrint(node->val);
		node = node->next;
	}
}