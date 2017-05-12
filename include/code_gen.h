#ifndef CODE_GEN_H_
#define CODE_GEN_H_

#include "list.h"	// TODO: move this include in code_gen.c and use a forward declaration

int stringLen(const char* str);

/**
 *	Generates three address code for addition of 
 * operand op1 and operand op2
 */
TAC* genAdd(char* op1, char* op2);

/**
 *	Generates three address code for subtraction of 
 * operand op1 and operand op2
 */
TAC* genSub(char* op1, char* op2);

/**
 *	Generates three address code for multiplication of 
 * operand op1 and operand op2
 */
TAC* genMul(char* op1, char* op2);

/**
 *	Generates three address code for division of 
 * operand op1 and operand op2
 */
TAC* genDiv(char* op1, char* op2);

/**
 *	Generates three address code for MCD of 
 * operand op1 and operand op2
 */
TAC* genMCD(const char* op1, const char* op2);

/**
 * Generates three address code instructions for addition
 * of fract op1 and fract op2.
 */
List* genFractSum(List* op1, List* op2);

/**
* Generates three address code instructions for subtraction
* of fract op1 and fract op2.
*/
List* genFractSub(List* op1, List* op2);

/**
* Generates three address code instructions for multiplication
* of fract op1 and fract op2.
*/
List* genFractMul(List* op1, List* op2);

/**
* Generates three address code instructions for division
* of fract op1 and fract op2.
*/
List* genFractDiv(List* op1, List* op2);

#endif 	// CODE_GEN_H_
