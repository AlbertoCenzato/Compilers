#include "node.h"

struct ThreeAddressCode {
	char* risul;
	char* op1;
	char* op;
	char* op2;
};

Node* createNode(TAC* tac) {
	Node* newNode = malloc(sizeof(Node));
	newNode->val = tac;
	//new->prev = NULL;
	newNode->next = NULL;
	return newNode;
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