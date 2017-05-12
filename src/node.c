#include "node.h"

#include <stdio.h>
#include <stdlib.h>

void tacPrint(TAC* tac) {
	printf("%s = %s %s %s\n", tac->risul, tac->op1, tac->op, tac->op2);
}

Node* nodeAlloc(TAC* tac) {
	Node* newNode = (Node*) malloc(sizeof(Node));
	newNode->val = tac;
	//new->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

void deleteTAC(TAC *tac) {
	if (tac == NULL)
		return;
	//free(tac->op);
	//free(tac->op1);
	//free(tac->op2);
	//free(tac->risul);
	free(tac);
}

void nodeFree(Node *node) {
	if (node == NULL)
		return;
	deleteTAC(node->val);
	free(node);
}