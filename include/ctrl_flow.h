#ifndef F_CTRL_FLOW_H_
#define F_CTRL_FLOW_H_

struct CodeList;
typedef struct CodeList CodeList;

//CodeList* ctrlGenConditionalJump(CodeList* booleanExpr, char* label);

/**
 *	\brief Generates three address code for an if statement
 *	\param bexpr: boolean expression used as if condition
 *	\param block: instructions contained in the if body
 */
CodeList* ctrlGenIf(CodeList* bexpr, CodeList* block);


/**
 *	\brief Effettua il backpatching della nextlist di unlabeledInstructions
 *			 con la prossima label disponibile e la assegna alla prima istruzione
 *			 di followingInstructions
 */
void ctrlBackpatch(CodeList* unlabeledInstructions, CodeList* followingInstructions);

#endif // F_CTRL_FLOW_H_