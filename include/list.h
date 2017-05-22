#ifndef LIST_H_
#define LIST_H_

struct ThreeAddressCode;	// forward declaration
typedef struct ThreeAddressCode TAC;

struct List;	// forward declaration to keep private struct members
typedef struct List List;

List* listAlloc();

void listFree(List *list);

//funzione per trovare l'ultimo nodo della lista
TAC* listGetLast(List* list);

TAC* listGetSecToLast(List* list);

//funzione aggiungere elemento in coda
void  listAdd(List *list, TAC *tac);

//unire due liste in cui l2 vene attaccata alla coda di l1
void listConcat(List *list1, List *list2);

/**
 *	@brief Prints a Three Address Code list to standard output
 *	@param list: list to be printed
 */
void listPrint(List* list);

#endif // LIST_H_
