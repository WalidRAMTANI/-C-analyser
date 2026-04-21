#ifndef COMPILER_H
#define COMPILER_H

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct variable_info; // forward declaration

// we're going to implement the symbol table.

// will have two structure to represent the element of the symbole table.
// the first structure will be for declaring structure and functions.
// the second structure will be the symbole table for declaring variables.

// the first structure will be like this:

// struct for the types we have in the language.

/*
type variable :
- identifiant : the name of the variable.
- type_var : the type of the variable [int, char, void, name-of-struct]
- type : the type of the variable.
- adresse : the address of the variable.
- liste_champs : the list of the fields of the variable if it is a structure.
TYPE STRUCTURE OR FUNCTIONS
identifiant : the name of the structure or function.
category : the category of the structure or function [structure, function]
adresse : the address of the structure or function.
liste_champs : the list of the fields of the structure or (arguments)function if
it is a structure.
*/
enum type_var { T_INT, T_CHAR, T_VOID, T_NULL };

enum kind { D_STRUCT, D_FUNC };

struct definition_info {
  enum kind kind;
  char *identifiant; // Name of the struct or function
  // For Functions:
  enum type_var return_type; // T_INT, T_CHAR, or T_VOID
  // For both:
  struct variable_info
      *liste_champs; // Fields (for struct) or Args (for function)
  struct variable_info *liste_locaux; // Local variables (for function)
  Node *body;                         // AST node for function body
  int total_size; // Sum of sizes of fields/locals (for memory/stack allocation)
};

enum type_nature { INT, CHAR, STRUCTURE };

struct variable_info {
  char *identifiant;
  enum type_nature type_nature;      // What is it? INT, CHAR, STRUCT
  struct definition_info *type_def;  // If it's a STRUCT, we link it here
  long adresse;                      // Stack offset or memory address
  struct variable_info *next;        // Next variable in list (fields/args)
  struct definition_info *container; // Containing function or structure
};

typedef enum { SYMBOL_VAR, SYMBOL_DEF, SYMBOL_EMPTY } SymbolType;

struct table_symbole {
  SymbolType type; // <--- The Tag
  union {
    struct variable_info *variable;
    struct definition_info *definition;
  } info;
};
extern struct table_symbole globalTable[100];
extern int size;
int is_in_table_symbole(char *identifiant, struct table_symbole *table,
                        int size);
void add_to_table_symbole(struct table_symbole *element,
                          struct table_symbole *table, int *size);
struct table_symbole fill_variable_declaration(Node *declarators, char *type);
void fill_struct_definition(Node *structNode);
void fill_function_definition(Node *funcNode, FILE *fp);
void fill_global_symbol_table(Node *root, struct table_symbole *globalTable, FILE *fp);
void print_global_symbol_table(struct table_symbole *globalTable, int size);
void parcours_instruction(Node *root, struct table_symbole *globalTable, FILE *file);
void check_all_declarations(Node *root, struct table_symbole *table, int tbl_size);
struct variable_info *find_variable(const char *name,
                                           struct definition_info *func,
                                           struct table_symbole *table,
                                           int tbl_size);
#endif