#ifndef FRACT_H_
#define FRACT_H_


struct List;	// forward declaration
typedef struct List List;

struct Fract {
	char* num;
	char* den;
};

typedef struct Fract Fract;

/**
*	@brief retireves the numerator of the fract represented
*			 by a sequence of Three Addrress Code instructions
*	@param list: list of three address code instructions
*/
char* fractNumFromList(List* list);

/**
*	@brief retireves the denominator of the fract represented
*			 by a sequence of Three Addrress Code instructions
*	@param list: list of three address code instructions
*/
char* fractDenFromList(List* list);

/**
* Generates three address code for the declaration
* of a new fract variable
*/
List* fractGenDecl();

/**
 *	@brief Generates three address code for the assignment
 *			 of an expression result to the given fract
 */
List* fractGenAssign(Fract* fract, List* list);
//List* fractGenAssign(char* num, char* den, List* list);

/**
 *	@brief Generates to temporay variables to store numerator
 *			 and denominator for a fract literal
 */
List* fractGenLiteral(Fract* fract);

/**
* Generates three address code instructions for addition
* of fract op1 and fract op2.
*/
List* fractGenSum(List* op1, List* op2);

/**
* Generates three address code instructions for subtraction
* of fract op1 and fract op2.
*/
List* fractGenSub(List* op1, List* op2);

/**
* Generates three address code instructions for multiplication
* of fract op1 and fract op2.
*/
List* fractGenMul(List* op1, List* op2);

/**
* Generates three address code instructions for division
* of fract op1 and fract op2.
*/
List* fractGenDiv(List* op1, List* op2);

#endif // FRACT_H_
