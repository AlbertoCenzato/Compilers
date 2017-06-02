#ifndef CODE_GEN_H_
#define CODE_GEN_H_

struct ThreeAddressCode;
typedef struct ThreeAddressCode TAC;

struct List;
typedef struct List List;


int stringLen(const char* str);

/**
 *	Generates three address code for variable declaration
 */
TAC* genDecl();

/**
 *	GEnerates three address code for variable assignment
 */
TAC* genAssign(char* val);

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
TAC* genMCD(char* op1, char* op2);

/**
 *	Generates three address code for equality comparision
 * between operand op1 and operand op2
 */
TAC* genEQ(char* op1, char* op2);

/**
 *	Generates three address code for inequality comparision
 * between operand op1 and operand op2
 */
TAC* genNE(char* op1, char* op2);

/**
 *	Generates three address code for logic and
 * between operand op1 and operand op2
 */
TAC* genAND(char* op1, char* op2);

/**
 *	Generates three address code for logic or
 * between operand op1 and operand op2
 */
TAC* genOR(char* op1, char* op2);

/**
 *	Generates three address code for less than comparision
 * between operand op1 and operand op2
 */
TAC* genLT(char* op1, char* op2);

/**
 *	Generates three address code for greater than comparision
 * between operand op1 and operand op2
 */
TAC* genGT(char* op1, char* op2);

/**
 *	Generates three address code for less than or equal comparision
 * between operand op1 and operand op2
 */
TAC* genLE(char* op1, char* op2);

/**
 *	Generates three address code for greater than or equal comparision
 * between operand op1 and operand op2
 */
TAC* genGE(char* op1, char* op2);


#endif 	// CODE_GEN_H_
