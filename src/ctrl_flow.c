#include "ctrl_flow.h"

#include <stddef.h>
#include <string.h>

#include "code_gen.h"
#include "code_list.h"
#include "tac.h"
#include "bool.h"

/*
CodeList* ctrlGenConditionalJump(CodeList* booleanExpr, char* label) {
	Bool b = boolFromList(booleanExpr);
	TAC* tac = genConditionalGoto(b, label);
}
*/

CodeList* ctrlGenIf(CodeList* bexpr, CodeList* block) {
	char* blockLabel = genNewLabel();
	TAC* tac = genConditionalGoto(boolFromList(bexpr), blockLabel);
	listAddBack(bexpr, tac);
	tacSetLabel(listGetFirst(block), blockLabel);
	tac = genGoto(NULL);
	listAddBack(bexpr, tac);
	listAddToNextList(bexpr, tac);
	tac = genGoto(NULL);
	listAddBack(block, tac);
	listAddToNextList(block, tac);
	
	return listConcat(bexpr, block);
}


// ---------- backpatch ----------

void patchTAC(TAC *tac, char *label) {
	char* oper = tacGetOper(tac);
	if (strcmp(oper, GEN_GOTO) == 0 || strcmp(oper, GEN_GOTOIFZ)) {
		tacSetOp2(tac, label);
	}
	else {
		tacSetLabel(tac, label);
	}
}

void ctrlBackpatch(CodeList* unlabeledInstructions, CodeList* followingInstructions) {
	
	CodeList* nextList = listGetNextList(unlabeledInstructions);
	if (nextList == NULL)
		return;

	char* label = genNewLabel();
	while (!listIsEmpty(nextList)) {
		TAC* tac = listPopFront(nextList);
		patchTAC(tac, label);
	}

	tacSetLabel(listGetFirst(followingInstructions), label);
}