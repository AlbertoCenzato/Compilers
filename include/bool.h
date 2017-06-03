#ifndef F_BOOL_H_
#define F_BOOL_H_

struct List;
typedef struct List List;

typedef char* Bool;

Bool boolFromList(List* list);

List* boolGenAND(List* op1, List* op2);

List* boolGenOR(List* op1, List* op2);

List* boolGenNOT(List* op1);


#endif // F_BOOL_H_