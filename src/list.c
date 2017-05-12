#include "../include/list.h"

#include <stdlib.h>

struct List {
	Node* head;
	Node* secToLast;
	int length;
};

List* listAlloc() {
	return (List*) malloc(sizeof(List));
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
	return list->secToLast->next;
}

Node* listFindSecToLast(List* list) {
	return list->secToLast;
}

void  listAdd(List *list, TAC *tac) {
	Node *last = list->secToLast->next;
	Node *newNode = createNode(tac);
	last->next = newNode;
	list->secToLast = last;
	list->length++;
}

void listConcat(List *list1, List *list2) {
	Node *last1 = list1->secToLast->next;
	last1->next = list2->head;
	list1->secToLast = list2->secToLast;
	list1->length += list2->length;
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
