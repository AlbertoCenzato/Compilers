#ifndef LIST_H_
#define LIST_H_

struct ThreeAddressCode;
typedef struct ThreeAddressCode TAC;

struct Node;
typedef struct Node Node;

struct List;	// forward declaration to keep private struct members

typedef struct List List;	// typedef for ease of use

List* listAlloc();

void listDelete(List *list);

//funzione per trovare l'ultimo nodo della lista
Node* listFindLast(List* list);

Node* listFindSecToLast(List* list);

//funzione aggiungere elemento in coda
void  listAdd(List *list, TAC *tac);

//unire due liste in cui l2 vene attaccata alla coda di l1
void listConcat(List *list1, List *list2);

#endif // LIST_H_
