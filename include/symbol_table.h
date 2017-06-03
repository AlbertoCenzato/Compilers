#ifndef F_SYMBOL_TABLE_H_
#define F_SYMBOL_TABLE_H_

#define TYPE_FRACT 1024
#define TYPE_BOOL  1025

struct Fract;						// forward declaration
typedef struct Fract Fract; 

typedef char* Bool;

/*
* @brief Adds fract variable with identifier "id" to symbol table
*/
void addFractVar(char *id);

/**
* @brief Adds bool variable with identifier "id" to symbol table
*/
void addBoolVar(char *id);


/**
* @brief Gets fract variable with identifier "id" from symbol table
*/
Fract* getFractVar(char *id);

/**
* @brief Gets bool variable with identifier "id" from symbol table
*/
Bool getBoolVar(char *id);


/**
 * @brief Assigns fract variable with identifier "id" the given
 *			 numerator and denominator.
 */
void setFractVar(char *id, char* num, char* den);

/**
* @brief Assigns fract variable with identifier "id" the given value.
*/
void setBoolVar(char *id, char* value);



#endif
