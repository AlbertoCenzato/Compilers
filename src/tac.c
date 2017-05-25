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
	if (tac->risul != NULL)
		printf("%s ", tac->risul);
	if (tac->op1 != NULL)
		printf("= %s ", tac->op1);
	if (tac->op != NULL)
		printf("%s ", tac->op);
	if (tac->op2 != NULL)
		printf("%s", tac->op2);
	printf("\n");
}
