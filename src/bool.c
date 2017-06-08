#include "bool.h"

#include "list.h"
#include "tac.h"
#include "code_gen.h"

Bool boolFromList(CodeList* list) {
	return tacGetRes(listGetLast(list));
}

/**
* @brief Generates three address code instructions for AND,
*			OR, NOT logic operations
* @op1: list of instructions for the computation of the first boolean.
* @op2: list of instructions for the computation of the second boolean.
* @sum: flag stating the operation to be computed on the two booleans:
*		  use 0 for AND, everityng else for OR.
*/
CodeList* boolGenANDOR(CodeList* op1, CodeList* op2, int or) {
	char* bool1 = boolFromList(op1);
	char* bool2 = boolFromList(op2);

	listConcat(op1, op2);
	TAC* tac = or ? genOR(bool1, bool2) : genAND(bool1, bool2);
	listAdd(op1, tac);

	return op1;
}

CodeList* boolGenAND(CodeList* op1, CodeList* op2) {
	return boolGenANDOR(op1, op2, 0);
}

CodeList* boolGenOR(CodeList* op1, CodeList* op2) {
	return boolGenANDOR(op1, op2, 1);
}

CodeList* boolGenNOT(CodeList* op1) {
	char* bool1 = boolFromList(op1);

	TAC* tac = genNOT(bool1);
	listAdd(op1, tac);

	return op1;
}