#include "../include/symbol_table.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------- struct and union definitions ----------

union varValue {
	Fract fract;
	Bool  bool;
};

struct variable {
	const char *id;            // we'll use this field as the key 
	union varValue* var;
	int type;
	UT_hash_handle hh; // makes this structure hashable 
};

typedef struct variable variable;


// ----------------------------------------------------

variable *mySymbolTable = NULL;


// ---------- private functions ----------

variable* addVar(char *id ) {
	variable *var;
	HASH_FIND_STR(mySymbolTable, id, var);
	if (var == NULL) {
		var = (variable*) malloc(sizeof(variable));
		var->id = id;
		HASH_ADD_KEYPTR(hh, mySymbolTable, var->id, strlen(var->id), var);	// gives ownership of id to mySymbolTable
	}
	else {
		printf("ERROR: multiple definition for	variable %s\n", id);
		exit(-1);
	}

	return var;
}

variable* getVar(char *id) {
	variable *tmp;
	HASH_FIND_STR(mySymbolTable, id, tmp);
	if (tmp == NULL) {
		printf("ERROR: variable %s is not defined\n", id);
		exit(-1);
	}
	return tmp;
}



// ---------- public functions ----------

void addFractVar(char *id) {
	variable* var = addVar(id);
	var->type = TYPE_FRACT;
}

void addBoolVar(char *id) {
	variable* var = addVar(id);
	var->type = TYPE_BOOL;
}

Fract* getFractVar(char* id) {
	variable* var = getVar(id);
	if (var->type != TYPE_FRACT) {
		printf("ERROR: trying to access non fract variable %s as fract!\n", id);
		exit(-1);
	}

	return &(var->var->fract);
}

Bool* getBoolVar(char* id) {
	variable* var = getVar(id);
	if (var->type != TYPE_BOOL) {
		printf("ERROR: trying to access non bool variable %s as bool!\n", id);
		exit(-1);
	}

	return &(var->var->bool);
}

void setFractVar(char *id, char *num, char *den) {
	Fract* fr = getFractVar(id);
	fr->num = num;
	fr->den = den;
}

void setBoolVar(char *id, char *value) {
	Bool *bl = getBoolVar(id);
	bl->value = value;
}