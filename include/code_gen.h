#ifndef CODE_GEN_H_
#define CODE_GEN_H_

#include "list.h"	// TODO: move this include in code_gen.c and use a forward declaration

int stringLen(char* str);

char* newVar();

/**
 *	Generates three address code for a generic binary operation
 */
TAC* genOp(char* op1, char* op2, char* operand);

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
 *	Generates three address code instructions for addition
 * or subtraction of fract op1 and fract op2.
 * @op1: list of instructions for the computation of the first fract.
 * @op2: list of instructions for the computation of the second fract.
 * @sum: flag stating if the two fracts must be added or subtracted,
 *			use 0 for subtraction, everything else for the addition.
 */
Node* genFractSumSub(Node* op1, Node* op2, int sum);

/**
 * Generates three address code instructions for addition
 * or subtraction of fract op1 and fract op2.
 */
Node* genFractSum(Node* op1, Node* op2);

Node* genFractSub(Node* op1, Node* op2);

Node* genFractMul(Node* op1, Node* op2);

Node* genFractDiv(Node* op1, Node* op2);

#endif 	// CODE_GEN_H_