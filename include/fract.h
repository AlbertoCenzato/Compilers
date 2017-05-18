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
* Generates three address code for the declaration
* of a new fract variable
*/
List* fractGenDecl();

/**
 *	@brief Generates three address code for the assignment
 *			 of an expression result to the given fract
 */
List* fractGenAssign(Fract* fr, List* list);

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
