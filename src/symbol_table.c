#include "../include/symbol_table.h"

#include "../extern_libs/uthash/uthash.h

variable *mySymbolTable = NULL;


void addFractVar(char *id) {
	variable *tmp;
	HASH_FIND_STR(mySymbolTable, id, tmp);
	if (tmp == NULL) {
		tmp = (variable*) malloc(sizeof(variable));
		tmp->id = id;
		//tmp->value = 0;
		tmp->type = TYPE_FRACT;
		HASH_ADD_KEYPTR(hh, mySymbolTable, tmp->id, strlen(tmp->id), tmp);	// gives ownership of id to mySymbolTable
	}
	else {
		printf("ERROR: multiple definition for	variable %s\n", id);
		exit(-1);
	}
}

void addBoolVar(char *id) {
	variable *tmp;
	HASH_FIND_STR(mySymbolTable, id, tmp);
	if (tmp == NULL) {
		tmp = (variable*) malloc(sizeof(variable));
		tmp->id = id;
		//tmp->value = 0;
		tmp->type = TYPE_BOOL;
		HASH_ADD_KEYPTR(hh, mySymbolTable, tmp->id, strlen(tmp->id), tmp);	// gives ownership of id to mySymbolTable
	}
	else {
		printf("ERROR: multiple definition for	variable %s\n", id);
		exit(-1);
	}
}


variable* findVar(char *id) {
	variable *tmp;
	HASH_FIND_STR(mySymbolTable, id, tmp);
	if (tmp == NULL) {
		printf("ERROR: variable %s is not defined\n", id);
		exit(-1);
	}
	return tmp;
}

void setFractVar(char *id, struct fract value) {
	variable *tmp;
	tmp = findVar(id);
	tmp->value.fr = value;
}

void setBoolVar(char *id, int value) {
	variable *tmp;
	tmp = findVar(id);
	tmp->value.bool = value;
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

struct fract getFractVar(char *id) {
	variable *tmp;
	tmp = getVar(id);
	if (tmp->type != TYPE_FRACT) {
		printf("ERROR: variable %s is not of type fract\n", id);
		exit(-1);
	}
	return tmp->value.fr;
}

int getBoolVar(char *id) {
	variable *tmp;
	tmp = getVar(id);
	if (tmp->type != TYPE_BOOL) {
		printf("ERROR: variable %s is not of type bool\n", id);
		exit(-1);
	}
	return tmp->value.bool;
}