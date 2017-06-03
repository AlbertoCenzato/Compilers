#ifndef F_FRACT_H_
#define F_FRACT_H_


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
 *	@brief Generates two temporay variables to store numerator
 *			 and denominator for a fract literal
 */
List* fractGenLiteral(Fract* fract);

/**
 *	@brief Generates two temporary variables to store numerator
 *			 and denominator for a fract identificator already present
 *			 in the symbol table
 */
List* fractGenID(Fract* fract);

/**
 * @brief Generates three address code instructions for addition
 *			 of fract op1 and fract op2.
 */
List* fractGenSum(List* op1, List* op2);

/**
 * @brief Generates three address code instructions for subtraction
 *			 of fract op1 and fract op2.
 */
List* fractGenSub(List* op1, List* op2);

/**
 * @brief Generates three address code instructions for multiplication
 *			 of fract op1 and fract op2.
 */
List* fractGenMul(List* op1, List* op2);

/**
 * @brief Generates three address code instructions for division
 *			 of fract op1 and fract op2.
 */
List* fractGenDiv(List* op1, List* op2);

/**
 *	@brief Generates three address code instructions for equality
 *			 comparision of fract op1 and fract op2.
 */
List* fractGenEQ(List* op1, List* op2);

/**
 * @brief Generates three address code instructions for inequality
 *			 comparision of fract op1 and fract op2.
 */
List* fractGenNE(List* op1, List* op2);

/**
 * @brief Generates three address code instructions for less than
 *			 comparision of fract op1 and fract op2.
 */
List * fractGenLT(List* op1, List* op2);

/**
 * @brief Generates three address code instructions for greater than
 *			 comparision of fract op1 and fract op2.
 */
List * fractGenGT(List* op1, List* op2);

/**
 * @brief Generates three address code instructions for less than or equal
 *			 comparision of fract op1 and fract op2.
 */
List * fractGenLE(List* op1, List* op2);

/**
 * @brief Generates three address code instructions for greater than or equal
 *			 comparision of fract op1 and fract op2.
 */
List * fractGenGE(List* op1, List* op2);

#endif // FRACT_H_
