#include "tac.h"

#include <stdio.h>
#include <stdlib.h>

TAC* tacAlloc() {
	return malloc(sizeof(TAC));
}

void tacFree(TAC *tac) {
	if (tac == NULL)
		return;
	//free(tac->op);
	//free(tac->op1);
	//free(tac->op2);
	//free(tac->risul);
	free(tac);
}

void tacPrint(TAC* tac) {
	printf("%s = %s %s %s\n", tac->risul, tac->op1, tac->op, tac->op2);
}
