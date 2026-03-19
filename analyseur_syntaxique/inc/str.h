/* str.h - Symbol Table Header */

#ifndef STR_H
#define STR_H

#include "tree.h"

// Type enumerations
enum TypeVar { TYPE_INT, TYPE_CHAR, TYPE_STRUCT, TYPE_VOID };
enum Type { TYPE_VAR, TYPE_FUNC };

// Variable structure
struct Var {
  char ident[64];        // the identifier
  enum TypeVar type_var; // the type of the variable
  enum Type type;        // Function or variable
  long adresse;
  union {
    struct Var *struct_type;
  };
};

// Symbol table structure
struct SymbolTable {
  struct Var table[1024];
  int count;
};

// Hash function
int hash(char *ident);

// Symbol table initialization
struct SymbolTable initSymbolTable();

// Add variable to symbol table
int addVar(struct SymbolTable *symbolTable, struct Var var);

// Question 2: Search and add functions
struct Var *searchVar(struct SymbolTable *symbolTable, char *ident);
int addVarIfNotExists(struct SymbolTable *symbolTable, struct Var var);

// Question 3: Fill global variables from AST
struct SymbolTable fillGlobalVars(Node *root);

// Utility function to display symbol table
void displaySymbolTable(struct SymbolTable *symbolTable);

#endif /* STR_H */
