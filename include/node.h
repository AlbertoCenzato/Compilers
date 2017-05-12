#ifndef NODE_H_
#define NODE_H_

struct ThreeAddressCode {
	char* risul;
	char* op1;
	char* op;
	char* op2;
};

typedef struct ThreeAddressCode TAC;

void tacPrint(TAC* tac);


struct Node {
	TAC* val;
	struct Node* next;
};

typedef struct Node Node;

//funzione per creare un nodo della lista
Node* nodeAlloc(TAC* tac);

void nodeFree(Node *node);

#endif // NODE_H_


