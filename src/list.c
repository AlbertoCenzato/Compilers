#include "list.h"

#include <stdlib.h>

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
}


// -------------------------------------------
// ---------------- List ---------------------
// -------------------------------------------

struct List {
	Node* head;
	Node* secToLast;
	int length;
};

List* listAlloc() {
	List *newList = (List*) malloc(sizeof(List));
	newList->length = 0;
	return newList;
}

void listFree(List *list) {
	Node *head;
	Node *next = list->head;
	while (next != NULL) {
		head = next;
		next = next->next;
		nodeFree(head);
	}

	free(list);
}

TAC* listGetLast(List* list) {
	if (list->length > 1)
		return list->secToLast->next->val;
	if (list->length == 1)
		return list->head->val;
	return NULL;	
}

TAC* listGetSecToLast(List* list) {
	if (list->length > 1)
		return list->secToLast->val;
	return NULL;
}

void listAdd(List *list, TAC *tac) {

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

void listConcat(List *list1, List *list2) {

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
	else {
		free(list1);
		list1 = list2;
	}
}

void listPrint(List* list) {
	Node* node = list->head;
	while(node != NULL) {
		tacPrint(node->val);
		node = node->next;
	}
}

/*
int main() {

	//provo la lista
	char op1[] = "10";
	char op2[] = "5";
	char two[] = "2";

	TAC *prova = genAdd(op1, op2);
	TAC *prova1 = genDiv(prova->risul, two);
	TAC *prova2 = genMul(prova1->risul, op2);

	List *list1 = listAlloc();
	listAdd(list1, prova);

	tacPrint(list1->head->val);

	listAdd(list1, prova1);
	tacPrint(listGetLast(list1));
	listAdd(list1, prova2);
	tacPrint(listGetLast(list1));

	List *list2 = listAlloc();
	TAC *prova4 = genMCD(prova->risul, op2);
	listAdd(list2, prova4);

	tacPrint(listGetLast(list2));

	listConcat(list1, list2);

	tacPrint(listGetLast(list1));

	listFree(list1);

}
*/