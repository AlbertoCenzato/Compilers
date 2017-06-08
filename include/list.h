#ifndef F_LIST_H_
#define F_LIST_H_

struct ThreeAddressCode;	// forward declaration
typedef struct ThreeAddressCode TAC;

struct CodeList;	// forward declaration to keep private struct members
typedef struct CodeList CodeList;

CodeList* listAlloc();

void listFree(CodeList *list);

//funzione per trovare l'ultimo nodo della lista
TAC* listGetLast(CodeList* list);

TAC* listGetSecToLast(CodeList* list);

//funzione aggiungere elemento in coda
void  listAdd(CodeList *list, TAC *tac);

//unire due liste in cui l2 vene attaccata alla coda di l1
void listConcat(CodeList *list1, CodeList *list2);

/**
 *	@brief Prints a Three Address Code list to standard output
 *	@param list: list to be printed
 */
void listPrint(CodeList* list);

#endif // LIST_H_
