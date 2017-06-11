#ifndef F_CODE_LIST_H_
#define F_CODE_LIST_H_

struct ThreeAddressCode;	// forward declaration
typedef struct ThreeAddressCode TAC;

struct CodeList;	// forward declaration to keep private struct members
typedef struct CodeList CodeList;

/**
 *	@brief allocates a new CodeList with malloc
 */
CodeList* listAlloc();

/**
 *	@brief deallocates a CodeList allocated with listAlloc()
 *			 recursively deallocating its contained elements
 */
void listFree(CodeList *list);

/**
 *	@brief Gives the lenght of the list
 */
int listLength(CodeList *list);

/**
 *	@brief Returns 0 if length is != 0
 */
int listIsEmpty(CodeList *list);

//funzione per trovare l'ultimo nodo della lista
TAC* listGetLast(CodeList* list);

TAC* listGetSecToLast(CodeList* list);

/**
 *	@brief Adds an element at the end of the list
 *	@param list: list to be extended
 *	@param tac: element to add to the list
 */
void  listAddBack(CodeList *list, TAC *tac);

/**
 *	@brief Removes the first element of the list and returns it
 *	@param codeList
 *	@return first element of the list
 */
TAC* listPopFront(CodeList* codeList);

//unire due liste in cui l2 vene attaccata alla coda di l1
CodeList* listConcat(CodeList* list1, CodeList* list2);

/**
 *	@brief Adds an incomplete goto three address code instruction 
 *			 to the nextlist of a CodeList
 *	@param codeList
 *	@param tac: incomplete goto
 */
void listAddToNextList(CodeList* codeList, TAC* tac);

/**
 *	@brief Returns the nextlist of the given CodeList
 *	@param codeList
 *	@return A code list representing the nextlist
 */
CodeList* listGetNextList(CodeList* codeList);


/**
 *	@brief Prints a Three Address Code list to standard output
 *	@param list: list to be printed
 */
void listPrint(CodeList* list);



/**
 *	@brief Effettua il backpatching della nextlist di unlabeledInstructions
 *			 con la prossima label disponibile e la assegna alla prima istruzione 
 *			 di followingInstructions
 */
void listBackpatch(CodeList* unlabeledInstructions, CodeList* followingInstructions);


#endif // LIST_H_
