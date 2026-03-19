#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct table_symbole globalTable[100];
int size = 0;
int offset = 0;

// helper function to get the size of a type.
static int get_size(enum type_nature type) {
  switch (type) {
  case INT:
    return sizeof(int);
  case CHAR:
    return sizeof(char);
  case STRUCTURE:
    return 0; // Size of a structure depends on its specific definition
  }
  return 0;
}
// implement a function to check if a symbole is in the table_symbole.
int is_in_table_symbole(char *identifiant, struct table_symbole *table,
                        int size) {
  if (!identifiant || !table)
    return 0;
  for (int i = 0; i < size; i++) {
    char *name = NULL;

    if (table[i].type == SYMBOL_VAR && table[i].info.variable != NULL) {
      name = table[i].info.variable->identifiant;
    } else if (table[i].type == SYMBOL_DEF &&
               table[i].info.definition != NULL) {
      name = table[i].info.definition->identifiant;
    }

    if (name != NULL && strcmp(name, identifiant) == 0) {
      return 1;
    }
  }
  return 0;
}

// helper to check for duplicate names in a linked list of variables
int is_in_variable_list(char *identifiant, struct variable_info *list) {
  while (list) {
    if (strcmp(list->identifiant, identifiant) == 0)
      return 1;
    list = list->next;
  }
  return 0;
}

// implement a function to add a symbole to the table_symbole.
void add_to_table_symbole(struct table_symbole *element,
                          struct table_symbole *table, int *size) {
  if (!element || !table)
    return;
  if (element->type == SYMBOL_VAR && element->info.variable != NULL &&
      is_in_table_symbole(element->info.variable->identifiant, table, *size)) {
    printf("Error: Variable %s already exists in the table.\n",
           element->info.variable->identifiant);
    return;
  } else if (element->type == SYMBOL_DEF && element->info.definition != NULL &&
             is_in_table_symbole(element->info.definition->identifiant, table,
                                 *size)) {
    printf("Error: Definition %s already exists in the table.\n",
           element->info.definition->identifiant);
    return;
  }
  table[*size] = *element;
  (*size)++;
}

struct definition_info *find_in_table_symbole(char *identifiant,
                                              struct table_symbole *table,
                                              int size) {
  if (!identifiant || !table)
    return NULL;
  for (int i = 0; i < size; i++) {
    char *name = NULL;

    if (table[i].type == SYMBOL_DEF && table[i].info.definition != NULL) {
      name = table[i].info.definition->identifiant;
    }

    if (name != NULL && strcmp(name, identifiant) == 0) {
      // i still didnt check if we've all the fields of the struct.
      return table[i].info.definition;
    }
  }
  return NULL;
}

struct variable_info *create_field_info(Node *declarator, char *type,
                                        int *local_offset,
                                        struct definition_info *container) {
  struct variable_info *q_variable = malloc(sizeof(struct variable_info));
  if (!q_variable) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }
  q_variable->identifiant = strdup(declarator->text);
  q_variable->next = NULL;
  q_variable->container = container;

  if (strcmp(type, "int") == 0) {
    q_variable->type_nature = INT;
  } else if (strcmp(type, "char") == 0) {
    q_variable->type_nature = CHAR;
  } else {
    q_variable->type_nature = STRUCTURE;
  }

  if (q_variable->type_nature == STRUCTURE) {
    q_variable->type_def = find_in_table_symbole(type, globalTable, size);
    if (q_variable->type_def == NULL) {
      printf("Error: Struct %s not found in the table.\n", type);
      free(q_variable->identifiant);
      free(q_variable);
      return NULL;
    }
  }

  q_variable->adresse = *local_offset;
  if (q_variable->type_nature == STRUCTURE) {
    *local_offset += q_variable->type_def->total_size;
  } else {
    *local_offset += get_size(q_variable->type_nature);
  }

  return q_variable;
}

void fill_struct_definition(Node *structNode) {
  if (!structNode || structNode->label != NODE_STRUCT_DEF)
    return;

  // Children: NODE_STRUCT, NODE_IDENT (name), NODE_DeclarateursStruct
  Node *nameNode = structNode->firstChild->nextSibling;
  Node *fieldsContainer = nameNode->nextSibling;

  struct definition_info *q_def = malloc(sizeof(struct definition_info));
  if (!q_def)
    return;

  q_def->identifiant = strdup(nameNode->text);
  q_def->liste_champs = NULL;
  q_def->liste_locaux = NULL;
  q_def->body = NULL;
  q_def->kind = D_STRUCT;
  q_def->total_size = 0;
  q_def->return_type = T_NULL;

  int local_offset = 0;
  struct variable_info **last_field = &(q_def->liste_champs);

  // NODE_DeclarateursStruct contains multiple NODE_VAR_DECL siblings
  Node *current_decl = fieldsContainer->firstChild;

  while (current_decl) {
    if (current_decl->label == NODE_VAR_DECL) {
      Node *typeNode = current_decl->firstChild;
      char *type_str = typeNode->text;

      // If it's "struct IDENT", text is in IDENT sibling
      if (typeNode->label == NODE_STRUCT) {
        type_str = typeNode->nextSibling->text;
      }

      // Re-evaluating declarators loop:
      Node *declarators = (typeNode->label == NODE_STRUCT)
                              ? typeNode->nextSibling->nextSibling
                              : typeNode->nextSibling;
      while (declarators && declarators->label == NODE_IDENT) {
        if (is_in_variable_list(declarators->text, q_def->liste_champs)) {
          printf("Error: Field %s already exists in struct %s.\n",
                 declarators->text, q_def->identifiant);
        } else {
          struct variable_info *new_field =
              create_field_info(declarators, type_str, &local_offset, q_def);
          if (new_field) {
            *last_field = new_field;
            last_field = &(new_field->next);
          }
        }
        declarators = declarators->nextSibling;
      }
    }
    current_decl = current_decl->nextSibling;
  }

  q_def->total_size = local_offset;

  struct table_symbole element;
  element.type = SYMBOL_DEF;
  element.info.definition = q_def;
  add_to_table_symbole(&element, globalTable, &size);
}

void fill_function_definition(Node *funcNode, FILE *fp) {
  if (!funcNode || funcNode->label != NODE_DeclFonct)
    return;

  // Children: EnTeteFonct, Corps
  Node *enTete = funcNode->firstChild;
  Node *corps = enTete->nextSibling;

  // enTete: TYPE/VOID/STRUCT, IDENT (name), Parametres
  Node *typeNode = enTete->firstChild;
  Node *nameNode = typeNode->nextSibling;
  Node *paramsNode = nameNode->nextSibling;

  struct definition_info *q_def = malloc(sizeof(struct definition_info));
  if (!q_def)
    return;

  q_def->kind = D_FUNC;
  q_def->identifiant = strdup(nameNode->text);
  // ------- partie TP5 partie 2 -------
  if(strcmp(q_def->identifiant, "main") == 0) {
      if(fp) {
        fprintf(fp, "section .data\n");
        fprintf(fp, "format db \"Value: %d\", 10, 0\n"); // Format string for printf
          fprintf(fp, "section .text\n");
          fprintf(fp, "global _start\n");
          fprintf(fp, "extern printf\n");
          fprintf(fp, "_start:\n");
      }
  }
  // ------- partie TP5 partie 2 -------
  
  q_def->liste_champs = NULL; // Parameters
  q_def->liste_locaux = NULL; // Locals
  q_def->body = corps;
  q_def->total_size = 0;

  // Handle return type
  if (typeNode->label == NODE_TYPE) {
    if (strcmp(typeNode->text, "int") == 0)
      q_def->return_type = T_INT;
    else
      q_def->return_type = T_CHAR;
  } else if (typeNode->label == NODE_VOID) {
    q_def->return_type = T_VOID;
  } else if (typeNode->label == NODE_STRUCT) {
    q_def->return_type = T_NULL; // Placeholder for struct return
  }

  // Process Parameters
  int param_offset = 0;
  struct variable_info **last_param = &(q_def->liste_champs);

  Node *p_item = paramsNode->firstChild;
  if (paramsNode->label == NODE_ListTypVar) {
    p_item =
        paramsNode
            ->firstChild; // ListTypVar IS the params node if not empty/void
  } else if (paramsNode->label == NODE_Parametres) {
    p_item = paramsNode->firstChild;
  }

  while (p_item && p_item->label != NODE_VOID) {
    // p_item is TYPE or STRUCT
    char *p_type = p_item->text;
    Node *p_ident = p_item->nextSibling;
    if (p_item->label == NODE_STRUCT) {
      p_type = p_ident->text;
      p_ident = p_ident->nextSibling;
    }

    if (is_in_variable_list(p_ident->text, q_def->liste_champs)) {
      printf("Error: Parameter %s already exists in function %s.\n",
             p_ident->text, q_def->identifiant);
    } else {
      struct variable_info *param =
          create_field_info(p_ident, p_type, &param_offset, q_def);
      if (param) {
        *last_param = param;
        last_param = &(param->next);
      }
    }
    p_item = p_ident->nextSibling;
  }

  // Process locals
  // Corps: DeclVars, SuiteInstr
  Node *declVarsNode = corps->firstChild;
  int local_offset = param_offset;
  struct variable_info **last_local = &(q_def->liste_locaux);

  if (declVarsNode && declVarsNode->label == NODE_DeclVars) {
    Node *current_var = declVarsNode->firstChild;
    while (current_var) {
      if (current_var->label == NODE_VAR_DECL && current_var->firstChild) {
        Node *l_typeNode = current_var->firstChild;
        char *l_type = l_typeNode->text;
        if (l_typeNode->label == NODE_STRUCT) {
          l_type = l_typeNode->nextSibling->text;
        }
        Node *declarator = (l_typeNode->label == NODE_STRUCT)
                               ? l_typeNode->nextSibling->nextSibling
                               : l_typeNode->nextSibling;
        while (declarator && declarator->label == NODE_IDENT) {
          if (is_in_variable_list(declarator->text, q_def->liste_champs) ||
              is_in_variable_list(declarator->text, q_def->liste_locaux)) {
            printf("Error: Local variable %s already exists in function %s (or "
                   "overlaps with parameter).\n",
                   declarator->text, q_def->identifiant);
          } else {
            struct variable_info *local =
                create_field_info(declarator, l_type, &local_offset, q_def);
            if (local) {
              *last_local = local;
              last_local = &(local->next);
            }
          }
          declarator = declarator->nextSibling;
        }
      }
      current_var = current_var->nextSibling;
    }
  }
  q_def->total_size = local_offset; // Stack frame size for locals

  struct table_symbole element;
  element.type = SYMBOL_DEF;
  element.info.definition = q_def;
  add_to_table_symbole(&element, globalTable, &size);
}

// implement a function for variable declaration.
struct table_symbole fill_variable_declaration(Node *declarators, char *type) {
  struct table_symbole element;
  element.type = SYMBOL_VAR;

  struct variable_info *q_variable = malloc(sizeof(struct variable_info));
  if (!q_variable) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }
  q_variable->identifiant = strdup(declarators->text);
  q_variable->next = NULL;
  q_variable->container = NULL; // Globals have no container struct/func

  if (strcmp(type, "int") == 0) {
    q_variable->type_nature = INT;
  } else if (strcmp(type, "char") == 0) {
    q_variable->type_nature = CHAR;
  } else {
    q_variable->type_nature = STRUCTURE;
  }

  if (q_variable->type_nature == STRUCTURE) {
    // For structures, we need to find the definition in the global table
    q_variable->type_def = find_in_table_symbole(type, globalTable, size);
    if (q_variable->type_def == NULL) {
      printf("Error: Struct %s not found in the table.\n", type);
      element.type = SYMBOL_EMPTY;
      if (q_variable->identifiant)
        free(q_variable->identifiant);
      free(q_variable); // Free allocated memory if struct not found
      return element;
    }
  }

  q_variable->adresse = offset;
  if (q_variable->type_nature == STRUCTURE) {
    offset += q_variable->type_def->total_size;
  } else {
    offset += get_size(q_variable->type_nature);
  }

  element.info.variable = q_variable;
  return element;
}
// implement a function to inititalse a table_symbole to a program of global
// variables.

void fill_global_symbol_table(Node *root, struct table_symbole *globalTable, FILE *fp) {
  if (!root || !globalTable)
    return;

  Node *current = root->firstChild;
  while (current) {
    if (current->label == NODE_DeclVars) {
      Node *var_node = current->firstChild;
      while (var_node) {
        if (var_node->label == NODE_VAR_DECL && var_node->firstChild) {
          Node *typeNode = var_node->firstChild;
          char *type_str = typeNode->text;
          if (typeNode->label == NODE_STRUCT) {
            type_str = typeNode->nextSibling->text;
          }
          Node *declarators = (typeNode->label == NODE_STRUCT)
                                  ? typeNode->nextSibling->nextSibling
                                  : typeNode->nextSibling;
          while (declarators != NULL) {
            struct table_symbole element =
                fill_variable_declaration(declarators, type_str);
            if (element.type != SYMBOL_EMPTY) {
              add_to_table_symbole(&element, globalTable, &size);
            }
            declarators = declarators->nextSibling;
          }
        } else if (var_node->label == NODE_STRUCT_DEF) {
          fill_struct_definition(var_node);
        }
        var_node = var_node->nextSibling;
      }
    } else if (current->label == NODE_DeclFoncts) {
      Node *func_node = current->firstChild;
      while (func_node) {
        if (func_node->label == NODE_DeclFonct) {
          fill_function_definition(func_node, fp);
        }
        func_node = func_node->nextSibling;
      }
    }
    current = current->nextSibling;
  }
}

static const char *get_type_name_str(enum type_nature type,
                                     struct definition_info *type_def) {
  switch (type) {
  case INT:
    return "int";
  case CHAR:
    return "char";
  case STRUCTURE:
    if (type_def && type_def->identifiant)
      return type_def->identifiant;
    return "struct";
  default:
    return "unknown";
  }
}

static const char *get_ret_type_str(enum type_var type) {
  switch (type) {
  case T_INT:
    return "int";
  case T_CHAR:
    return "char";
  case T_VOID:
    return "void";
  default:
    return "-";
  }
}

void print_global_symbol_table(struct table_symbole *globalTable, int size) {
  if (!globalTable)
    return;

  printf("\n+------------------------------------------------------------------"
         "---------+\n");
  printf("|                            GLOBAL SYMBOL TABLE                     "
         "        |\n");
  printf("+----------------------+------------+------------+-----------+-------"
         "--------+\n");
  printf("| %-20s | %-10s | %-10s | %-9s | %-13s |\n", "Identifier", "Kind",
         "Type", "Offset", "Size/Ret");
  printf("+----------------------+------------+------------+-----------+-------"
         "--------+\n");

  for (int i = 0; i < size; i++) {
    if (globalTable[i].type == SYMBOL_VAR &&
        globalTable[i].info.variable != NULL) {
      struct variable_info *var = globalTable[i].info.variable;
      printf("| %-20s | %-10s | %-10s | %-9ld | %-13s |\n", var->identifiant,
             "GLOBAL", get_type_name_str(var->type_nature, var->type_def),
             var->adresse, "");
    } else if (globalTable[i].type == SYMBOL_DEF &&
               globalTable[i].info.definition != NULL) {
      struct definition_info *def = globalTable[i].info.definition;
      const char *kind = (def->kind == D_STRUCT) ? "STRUCT" : "FUNC";
      const char *type =
          (def->kind == D_STRUCT) ? "" : get_ret_type_str(def->return_type);

      char info_str[16];
      if (def->kind == D_STRUCT) {
        snprintf(info_str, 16, "Sz: %d", def->total_size);
      } else {
        snprintf(info_str, 16, "Stk: %d", def->total_size);
      }

      printf("| %-20s | %-10s | %-10s | %-9s | %-13s |\n", def->identifiant,
             kind, type, "-", info_str);

      // Print fields/params
      struct variable_info *p = def->liste_champs;
      const char *subkind = (def->kind == D_STRUCT) ? "FIELD" : "PARAM";
      while (p) {
        char indent_name[30];
        snprintf(indent_name, 30, "  %s", p->identifiant);
        printf("| %-20s | %-10s | %-10s | %-9ld | %-13s |\n", indent_name,
               subkind, get_type_name_str(p->type_nature, p->type_def),
               p->adresse, "");
        p = p->next;
      }

      // Print locals
      struct variable_info *l = def->liste_locaux;
      while (l) {
        char indent_name[30];
        snprintf(indent_name, 30, "  %s", l->identifiant);
        printf("| %-20s | %-10s | %-10s | %-9ld | %-13s |\n", indent_name,
               "LOCAL", get_type_name_str(l->type_nature, l->type_def),
               l->adresse, "");
        l = l->next;
      }
      printf("+----------------------+------------+------------+-----------+---"
             "------------+\n");
    }
  }
  printf("\n");
}
