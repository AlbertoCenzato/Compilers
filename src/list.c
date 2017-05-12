#include "list.h"

#include <stdlib.h>

#include "node.h"

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

void listDelete(List *list) {
	Node *head;
	Node *next = list->head;
	while (next != NULL) {
		head = next;
		next = next->next;
		deleteNode(head);
	}

	free(list);
}

Node* listFindLast(List* list) {
	if (list->length > 1)
		return list->secToLast->next;
	if (list->length == 1)
		return list->head;
	return NULL;	
}

Node* listFindSecToLast(List* list) {
	if (list->length > 1)
		return list->secToLast;
	return NULL;
}

void listAdd(List *list, TAC *tac) {

	Node *newNode = createNode(tac);

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



/*
int main() {

	//provo la lista
	TAC *prova = malloc(sizeof(TAC));
	TAC *prova1 = malloc(sizeof(TAC));
	TAC *prova2 = malloc(sizeof(TAC));
	TAC *prova3 = malloc(sizeof(TAC));

	prova->risul = "000";
	prova1->risul = "001";
	prova2->risul = "002";
	prova3->risul = "003";

	Node *head = createNode(prova);

	printf("----->%s\n", (head->val)->risul);

	addToList(head, prova1);
	printf("----->%s\n", (findLast(head)->val)->risul);
	addToList(head, prova2);
	printf("----->%s\n", (findLast(head)->val)->risul);
	addToList(head, prova3);
	printf("----->%s\n", (findLast(head)->val)->risul);

	deleteList(head);

}
*/
