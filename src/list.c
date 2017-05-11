#include "../include/list.h"

Node* createNode(TAC* tac) {
	Node* newNode = malloc(sizeof(Node));
	newNode->val = tac;
	//new->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

Node* findLast(Node* l) {

	if (l->next == NULL)
		return l;
	else
		return findLast(l->next);
}

Node* findSecToLast(Node* node) {

	if (node == NULL)
		return NULL;

	Node *secToLast = NULL;
	Node *last = node;
	while (last->next != NULL) {
		secToLast = last;
		last = last->next;
	}

	return secToLast;
}

void  addToList(Node *head, TAC *tac) {
	//Node* p;
	//Node* coda;
	Node *p = findLast(head);
	Node *newNode = (createNode(tac));
	p->next = newNode;
	//p->next->prev = p;   
}

void concat(Node *lista1, Node *lista2) {
	Node *p = findLast(lista1);
	p->next = lista2;
}

void deleteTAC(TAC *tac) {
	if (tac == NULL)
		return;
	free(tac->op);
	free(tac->op1);
	free(tac->op2);
	free(tac->risul);
	free(tac);
}

void deleteNode(Node *node) {
	if (node == NULL)
		return;
	deleteTAC(node->val);
	free(node);
}

void deleteList(Node *head) {
	Node *next = head->next;
	deleteNode(head);
	if (next == NULL)
		return;
	deleteList(next);
}

int main() {

	//provo la lista
	TAC *prova = malloc(sizeof(ThreeAddressCode));
	TAC *prova1 = malloc(sizeof(ThreeAddressCode));
	TAC *prova2 = malloc(sizeof(ThreeAddressCode));
	TAC *prova3 = malloc(sizeof(ThreeAddressCode));

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