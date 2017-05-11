#ifndef SYMBOL_TABLE_H_
#define SYMBOL_TABLE_H_

#define TYPE_FRACT 1024
#define TYPE_BOOL  1025

union varValue {
	struct fract fr;
	int bool;
};

struct variable {
    const char *id;            // we'll use this field as the key 
    union varValue value;
	 int type;
    UT_hash_handle hh; // makes this structure hashable 
};

typedef struct variable variable;


/*
* add variable to symbol table
*/
void addFractVar(char *id);

void addBoolVar(char *id);

/*
* update variable "id" in the symbol table
*/
variable* findVar(char *id);

void setFractVar(char *id, struct fract value);

void setBoolVar(char *id, int value);

/*
* read variable "id" in the symbol table
*/
variable* getVar(char *id);

struct fract getFractVar(char *id);

int getBoolVar(char *id);

#endif
