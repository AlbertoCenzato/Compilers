#ifndef F_TAC_H_
#define F_TAC_H_

struct ThreeAddressCode; //{
//	char* risul;
//	char* op1;
//	char* op;
//	char* op2;
//};

typedef struct ThreeAddressCode TAC;

TAC* tacAlloc();

void tacFree(TAC *tac);

void tacPrint(TAC* tac);

void tacSetOp1(TAC* tac, char* op1);

void tacSetOp2(TAC* tac, char* op2);

void tacSetOper(TAC* tac, char* oper);

void tacSetRes(TAC* tac, char* res);

char* tacGetOp1(TAC* tac);

char* tacGetOp2(TAC* tac);

char* tacGetOper(TAC* tac);

char* tacGetRes(TAC* tac);

#endif // TAC_H_


