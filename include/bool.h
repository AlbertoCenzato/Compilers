#ifndef F_BOOL_H_
#define F_BOOL_H_

struct CodeList;
typedef struct CodeList CodeList;

typedef char* Bool;

Bool boolFromList(CodeList* list);

CodeList* boolGenAND(CodeList* op1, CodeList* op2);

CodeList* boolGenOR(CodeList* op1, CodeList* op2);

CodeList* boolGenNOT(CodeList* op1);


#endif // F_BOOL_H_