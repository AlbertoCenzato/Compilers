#ifndef TAC_H_
#define TAC_H_

struct ThreeAddressCode {
	char* risul;
	char* op1;
	char* op;
	char* op2;
};

typedef struct ThreeAddressCode TAC;

TAC* tacAlloc();

void tacFree(TAC *tac);

void tacPrint(TAC* tac);

#endif // TAC_H_


