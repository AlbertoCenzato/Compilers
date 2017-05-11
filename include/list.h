#ifndef LIST_H_
#define LIST_H_

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>

struct ThreeAddressCode {
	char* risul;
	char* op1;
	char* op;
	char* op2;
};

typedef struct ThreeAddressCode TAC;


struct Node { 
	//struct List * prev;
	TAC* val;
	struct Node* next;
};

typedef struct Node Node;


//funzione per creare un nodo della lista
Node* createNode(TAC* tac);

//funzione per trovare l'ultimo nodo della lista
Node* findLast(Node* l);

Node* findSecToLast(Node* node);

//funzione aggiungere elemento in coda
void  addToList(Node *head, TAC *tac);


//unire due liste in cui l2 vene attaccata alla coda di l1
void concat(Node *lista1, Node *lista2);

void deleteTAC(TAC *tac);

void deleteNode(Node *node);

void deleteList(Node *head);

#endif // LIST_H_
