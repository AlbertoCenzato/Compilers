#ifndef CODE_GEN_H_
#define CODE_GEN_H_

#include "list.h"	// TODO: move this include in code_gen.c and use a forward declaration

int stringLen(const char* str);

//char* newVar();

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
Node* genFractSum(Node* op1, Node* op2);

/**
* Generates three address code instructions for subtraction
* of fract op1 and fract op2.
*/
Node* genFractSub(Node* op1, Node* op2);

/**
* Generates three address code instructions for multiplication
* of fract op1 and fract op2.
*/
Node* genFractMul(Node* op1, Node* op2);

/**
* Generates three address code instructions for division
* of fract op1 and fract op2.
*/
Node* genFractDiv(Node* op1, Node* op2);

#endif 	// CODE_GEN_H_
