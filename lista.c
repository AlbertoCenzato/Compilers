#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ThreeAddressCode {
	char* risul;
	char* op1;
	char* op;
	char* op2;
};

typedef struct ThreeAddressCode ThreeAddressCode;


struct Node { 
	//struct List * prev;
	ThreeAddressCode* val;
	struct Node* next;
};

typedef struct Node Node;


//funzione per creare un nodo della lista
Node* createNode(ThreeAddressCode* tac){
	Node* newNode = malloc(sizeof(Node));
	newNode->val = tac;
	//new->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

//funzione per trovare l'ultimo nodo della lista
Node* findLast(Node* l){
	
	if (l->next == NULL){
	 return l;
	}
	else return findLast(l->next);
	
}

//funzione aggiungere elemento in coda
void  addToList(Node *head, ThreeAddressCode *tac){
	//Node* p;
	//Node* coda;
	Node *p = findLast(head);
	Node *newNode = (createNode(tac));
	p->next = newNode;
	//p->next->prev = p;   
}


//unire due liste in cui l2 vene attaccata alla coda di l1
void concat(Node *lista1, Node *lista2){
	Node *p = findLast(lista1);
	p->next = lista2;  
}

void deleteTAC(ThreeAddressCode *tac) {
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


int main()
{

//provo la lista
ThreeAddressCode *prova  = malloc(sizeof(ThreeAddressCode));
ThreeAddressCode *prova1 = malloc(sizeof(ThreeAddressCode));
ThreeAddressCode *prova2 = malloc(sizeof(ThreeAddressCode));
ThreeAddressCode *prova3 = malloc(sizeof(ThreeAddressCode));

prova ->risul = "000";
prova1->risul = "001";
prova2->risul = "002";
prova3->risul = "003";

Node *head = createNode(prova);

printf("----->%s\n", (head->val)->risul );

addToList(head,prova1);
printf("----->%s\n", (findLast(head)->val)->risul);
addToList(head,prova2);
printf("----->%s\n", (findLast(head)->val)->risul);
addToList(head,prova3);
printf("----->%s\n", (findLast(head)->val)->risul);

deleteList(head);

}
