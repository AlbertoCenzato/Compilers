#ifndef NODE_H_
#define NODE_H_

struct TAC;
typedef struct TAC TAC;

struct Node {
	//struct List * prev;
	TAC* val;
	struct Node* next;
};

typedef struct Node Node;

//funzione per creare un nodo della lista
Node* createNode(TAC* tac);

void deleteNode(Node *node);

#endif // NODE_H_


