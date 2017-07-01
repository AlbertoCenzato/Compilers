#include "ctrl_flow.h"

#include <string.h>

#include "code_gen.h"
#include "code_list.h"
#include "tac.h"
#include "bool.h"


// ---------- backpatch ----------

void patchTAC(TAC *tac, char *label) {
	char* oper = tacGetOper(tac);
	if (strcmp(oper, GEN_GOTO) == 0 || strcmp(oper, GEN_GOTOIFNZ)) {
		tacSetOp2(tac, label);
	}
	else {
		tacSetLabel(tac, label);
	}
}

void ctrlBackpatch(CodeList* unlabeledInstructions, CodeList* followingInstructions) {

	if (listIsEmpty(followingInstructions))
		return;

	CodeList* nextList = listGetNextList(unlabeledInstructions);
	if (listIsEmpty(nextList))
		return;

	char* label = genNewLabel();
	while (!listIsEmpty(nextList)) {
		TAC* tac = listPopFront(nextList);
		patchTAC(tac, label);
	}

	tacSetLabel(listGetFirst(followingInstructions), label);
}




// ---------- flow of control generation ----------

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

CodeList* ctrlGenIfElse(CodeList* bexpr, CodeList* iftrue, CodeList* iffalse) {
	char* iftrueLabel  = genNewLabel();
	char* iffalseLabel = genNewLabel();

	// true
	TAC* tac = genConditionalGoto(boolFromList(bexpr), iftrueLabel);
	listAddBack(bexpr, tac);
	tacSetLabel(listGetFirst(iftrue), iftrueLabel);

	// false
	tac = genGoto(iffalseLabel);
	listAddBack(bexpr, tac);
	tacSetLabel(listGetFirst(iffalse), iffalseLabel);

	tac = genGoto(NULL);
	listAddBack(iftrue, tac);
	listAddToNextList(iftrue, tac);

	tac = genGoto(NULL);
	listAddBack(iffalse, tac);
	listAddToNextList(iffalse, tac);

	return listConcat(listConcat(bexpr, iftrue), iffalse);
}

CodeList* ctrlGenWhile(CodeList* bexpr, CodeList* block) {
	char* bexprLabel = genNewLabel();
	char* blockLabel = genNewLabel();

	tacSetLabel(listGetFirst(bexpr), bexprLabel); // assign a label to bexpr
	tacSetLabel(listGetFirst(block), blockLabel); // assign a label to block

	// If bexpr true jump to "block" execution
	TAC* tac = genConditionalGoto(boolFromList(bexpr), blockLabel);
	listAddBack(bexpr, tac);

	// If bexpr false jump to next instruction.
	// Label leved empty, will be backpatched later
	tac = genGoto(NULL);
	listAddBack(bexpr, tac);
	listAddToNextList(bexpr, tac);


	CodeList* nextList = listGetNextList(block);
	if (listIsEmpty(nextList)) {
		tac = genGoto(bexprLabel);
		listAddBack(block, tac);
	}
	else {	// if block needs backpatch assign bexpr as next instruction
		while (!listIsEmpty(nextList)) {
			tac = listPopFront(nextList);
			patchTAC(tac, bexprLabel);
		}
	}

	return listConcat(bexpr, block);
}
