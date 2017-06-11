#ifndef F_TAC_H_
#define F_TAC_H_

struct ThreeAddressCode;
typedef struct ThreeAddressCode TAC;

TAC* tacAlloc();

void tacFree(TAC *tac);

void tacPrint(TAC* tac);

void tacSetLabel(TAC* tac, char* label);

void tacSetOp1(TAC* tac, char* op1);

void tacSetOp2(TAC* tac, char* op2);

void tacSetOper(TAC* tac, char* oper);

void tacSetRes(TAC* tac, char* res);

char* tacGetLabel(TAC* tac);

char* tacGetOp1(TAC* tac);

char* tacGetOp2(TAC* tac);

char* tacGetOper(TAC* tac);

char* tacGetRes(TAC* tac);

void tacPatch(TAC* tac, char* label);

#endif // TAC_H_


