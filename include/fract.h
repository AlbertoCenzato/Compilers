#ifndef F_FRACT_H_
#define F_FRACT_H_


struct CodeList;	// forward declaration
typedef struct CodeList CodeList;

struct Fract {
	char* num;
	char* den;
};

typedef struct Fract Fract;

/**
*	\brief retireves the numerator of the fract represented
*			 by a sequence of Three Addrress Code instructions
*	\param list: list of three address code instructions
*/
char* fractNumFromList(CodeList* list);

/**
*	\brief retireves the denominator of the fract represented
*			 by a sequence of Three Addrress Code instructions
*	\param list: list of three address code instructions
*/
char* fractDenFromList(CodeList* list);

/**
* \brief Generates three address code for the declaration
*			of a new fract variable
*/
CodeList* fractGenDecl();

/**
 *	\brief Generates three address code for the assignment
 *			 of an expression result to the given fract
 */
CodeList* fractGenAssign(Fract* fract, CodeList* list);
//CodeList* fractGenAssign(char* num, char* den, CodeList* list);

/**
 *	\brief Generates two temporay variables to store numerator
 *			 and denominator for a fract literal
 */
CodeList* fractGenLiteral(Fract* fract);

/**
 *	\brief Generates two temporary variables to store numerator
 *			 and denominator for a fract identificator already present
 *			 in the symbol table
 */
CodeList* fractGenID(Fract* fract);

/**
 * \brief Generates three address code instructions for addition
 *			 of fract op1 and fract op2.
 */
CodeList* fractGenSum(CodeList* op1, CodeList* op2);

/**
 * \brief Generates three address code instructions for subtraction
 *			 of fract op1 and fract op2.
 */
CodeList* fractGenSub(CodeList* op1, CodeList* op2);

/**
 * \brief Generates three address code instructions for multiplication
 *			 of fract op1 and fract op2.
 */
CodeList* fractGenMul(CodeList* op1, CodeList* op2);

/**
 * \brief Generates three address code instructions for division
 *			 of fract op1 and fract op2.
 */
CodeList* fractGenDiv(CodeList* op1, CodeList* op2);

/**
 *	\brief Generates three address code instructions for equality
 *			 comparision of fract op1 and fract op2.
 */
CodeList* fractGenEQ(CodeList* op1, CodeList* op2);

/**
 * \brief Generates three address code instructions for inequality
 *			 comparision of fract op1 and fract op2.
 */
CodeList* fractGenNE(CodeList* op1, CodeList* op2);

/**
 * \brief Generates three address code instructions for less than
 *			 comparision of fract op1 and fract op2.
 */
CodeList * fractGenLT(CodeList* op1, CodeList* op2);

/**
 * \brief Generates three address code instructions for greater than
 *			 comparision of fract op1 and fract op2.
 */
CodeList * fractGenGT(CodeList* op1, CodeList* op2);

/**
 * \brief Generates three address code instructions for less than or equal
 *			 comparision of fract op1 and fract op2.
 */
CodeList * fractGenLE(CodeList* op1, CodeList* op2);

/**
 * \brief Generates three address code instructions for greater than or equal
 *			 comparision of fract op1 and fract op2.
 */
CodeList * fractGenGE(CodeList* op1, CodeList* op2);

#endif // FRACT_H_
