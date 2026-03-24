#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct table_symbole globalTable[100];
int size = 0;
int offset = 0;

// initialise the table symbole with the global functions of C library.
void init_global_table() {
  // add getchar
  struct definition_info *getchar_def = malloc(sizeof(struct definition_info));
  getchar_def->identifiant = strdup("getchar");
  getchar_def->kind = D_FUNC;
  getchar_def->return_type = T_CHAR;
  getchar_def->liste_champs = NULL;
  getchar_def->liste_locaux = NULL;
  getchar_def->body = NULL;
  getchar_def->total_size = 0;
  // create a table_symbole for getchar and add it to the global table.
  struct table_symbole getchar_element;
  getchar_element.type = SYMBOL_DEF;
  getchar_element.info.definition = getchar_def;
  add_to_table_symbole(&getchar_element, globalTable, &size);

  // add putchar
  struct definition_info *putchar_def = malloc(sizeof(struct definition_info));
  putchar_def->identifiant = strdup("putchar");
  putchar_def->kind = D_FUNC;
  putchar_def->return_type = T_VOID;
  putchar_def->liste_champs = malloc(sizeof(struct variable_info));
  putchar_def->liste_champs->identifiant = strdup("c");
  putchar_def->liste_champs->type_nature = CHAR;
  putchar_def->liste_champs->next = NULL;
  putchar_def->liste_locaux = NULL;
  putchar_def->body = NULL;
  putchar_def->total_size = 1; // 1 byte for the char parameter
  // create a table_symbole for putchar and add it to the global table.
  struct table_symbole putchar_element;
  putchar_element.type = SYMBOL_DEF;
  putchar_element.info.definition = putchar_def;
  add_to_table_symbole(&putchar_element, globalTable, &size);

// add getint
  struct definition_info *getint_def = malloc(sizeof(struct definition_info));
  getint_def->identifiant = strdup("getint");
  getint_def->kind = D_FUNC;
  getint_def->return_type = T_INT;
  getint_def->liste_champs = NULL;
  getint_def->liste_locaux = NULL;
  getint_def->body = NULL;
  getint_def->total_size = 0;
  // create a table_symbole for getint and add it to the global table.
  struct table_symbole getint_element;
  getint_element.type = SYMBOL_DEF;
  getint_element.info.definition = getint_def;
  add_to_table_symbole(&getint_element, globalTable, &size);

  // add putint
  struct definition_info *putint_def = malloc(sizeof(struct definition_info));
  putint_def->identifiant = strdup("putint");
  putint_def->kind = D_FUNC;
  putint_def->return_type = T_VOID;
  putint_def->liste_champs = malloc(sizeof(struct variable_info));
  putint_def->liste_champs->identifiant = strdup("n");
  putint_def->liste_champs->type_nature = INT;
  putint_def->liste_champs->next = NULL;
  putint_def->liste_locaux = NULL;
  putint_def->body = NULL;
  putint_def->total_size = 4; // 4 bytes for the int parameter
  // create a table_symbole for putint and add it to the global table.
  struct table_symbole putint_element;
  putint_element.type = SYMBOL_DEF;
  putint_element.info.definition = putint_def;
  add_to_table_symbole(&putint_element, globalTable, &size);
}

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

  // enTete: TYPE/VOID IDENT Parametres, or STRUCT IDENT(type) IDENT(name) Parametres
  Node *typeNode = enTete->firstChild;
  Node *nameNode = typeNode->nextSibling;
  // Pour les fonctions retournant un struct: STRUCT, IDENT(type), IDENT(name), Parametres
  if (typeNode->label == NODE_STRUCT) {
    nameNode = nameNode->nextSibling;
  }
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
        fprintf(fp, "format db \"Value: %%d\", 10, 0\n"); // Format string for printf
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
      /* Gérer les définitions de struct locales */
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
      } else if (current_var->label == NODE_STRUCT_DEF) {
        fill_struct_definition(current_var);
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
  // initialize the global table with the standard library functions
  init_global_table();
  Node *current = root->firstChild;
  while (current) {
    if (current->label == NODE_DeclVars) {
      // handle global variable declarations
      if(fp){
        fprintf(fp, "section .bss\n");
      }
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
            // allocate space in .bss for global variable
            if(fp){
              struct variable_info *var_info = element.info.variable;
              if(var_info && var_info->type_nature ==  INT) {
                fprintf(fp, " %s resd 1\n", var_info->identifiant);
              }else if(var_info && var_info->type_nature == CHAR) {
                fprintf(fp, " %s resb 1\n", var_info->identifiant);
              } else if(var_info && var_info->type_nature == STRUCTURE) {
                fprintf(fp, " %s resb %d\n", var_info->identifiant, var_info->type_def->total_size);
              }
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




/* ===== TDC6 Exercice 1 : Vérification des déclarations ===== */

/* Recherche une variable dans les paramètres, locaux de la fonction, et les globales */
static struct variable_info *find_variable(const char *name,
                                           struct definition_info *func,
                                           struct table_symbole *table,
                                           int tbl_size) {
  if (!name) return NULL;
  /* Paramètres de la fonction courante */
  if (func) {
    struct variable_info *p = func->liste_champs;
    while (p) {
      if (strcmp(p->identifiant, name) == 0) return p;
      p = p->next;
    }
    /* Variables locales de la fonction courante */
    struct variable_info *l = func->liste_locaux;
    while (l) {
      if (strcmp(l->identifiant, name) == 0) return l;
      l = l->next;
    }
  }
  /* Variables globales */
  for (int i = 0; i < tbl_size; i++) {
    if (table[i].type == SYMBOL_VAR && table[i].info.variable &&
        strcmp(table[i].info.variable->identifiant, name) == 0) {
      return table[i].info.variable;
    }
  }
  return NULL;
}

/* Forward declaration de get_expr_type */
static enum type_nature get_expr_type(Node *expr, struct definition_info *func,
                             struct table_symbole *table, int tbl_size, struct definition_info **struct_def);

/* Vérifie un seul nœud (sans parcourir ses frères) */
static void check_node(Node *node, struct definition_info *func,
                        struct table_symbole *table, int tbl_size);

/* Vérifie un nœud et tous ses frères */
static void check_node_list(Node *node, struct definition_info *func,
                             struct table_symbole *table, int tbl_size) {
  while (node) {
    check_node(node, func, table, tbl_size);
    node = node->nextSibling;
  }
}

static void check_node(Node *node, struct definition_info *func,
                        struct table_symbole *table, int tbl_size) {
  if (!node) return;

  switch (node->label) {

  case NODE_IDENT:
    if (node->firstChild && node->firstChild->label == NODE_Arguments) {
      /* Appel de fonction via la règle Value : IDENT '(' Arguments ')' */
      if (!find_in_table_symbole(node->text, table, tbl_size)) {
        fprintf(stderr, "Error line %d: undeclared function '%s'\n",
                node->lineno, node->text);
      }
      /* Vérifier les expressions dans les arguments */
      check_node_list(node->firstChild, func, table, tbl_size);
    } else {
      /* Référence simple à une variable / paramètre */
      if (!find_variable(node->text, func, table, tbl_size) &&
          !find_in_table_symbole(node->text, table, tbl_size)) {
        fprintf(stderr, "Error line %d: undeclared identifier '%s'\n",
                node->lineno, node->text);
      }
    }
    break;

  case NODE_CALL_FUNCTION:
    /* Premier enfant = nom de la fonction (NODE_IDENT), second = Arguments */
    if (node->firstChild && node->firstChild->label == NODE_IDENT) {
      if (!find_in_table_symbole(node->firstChild->text, table, tbl_size)) {
        fprintf(stderr, "Error line %d: undeclared function '%s'\n",
                node->firstChild->lineno, node->firstChild->text);
      }
    }
    /* Vérifier les arguments (on saute le nom de la fonction) */
    if (node->firstChild && node->firstChild->nextSibling) {
      check_node_list(node->firstChild->nextSibling, func, table, tbl_size);
    }
    break;

  case NODE_DOT:
    /* Accès membre : on vérifie seulement la partie gauche (la variable),
       pas le nom du champ à droite */
    if (node->firstChild) {
      check_node(node->firstChild, func, table, tbl_size);
    }
    break;

  case NODE_DeclVars:
    /* Déclarations de variables : on ne les vérifie pas ici, elles définissent
       des variables */
    break;
  case NODE_ASSIGN:
    {
      Node *lvalue = node->firstChild;
      Node *rvalue = lvalue ? lvalue->nextSibling : NULL;
      if (lvalue && rvalue) {
        check_node(lvalue, func, table, tbl_size);
        check_node(rvalue, func, table, tbl_size);
        enum type_nature ltype = get_expr_type(lvalue, func, table, tbl_size, NULL);
        enum type_nature rtype = get_expr_type(rvalue, func, table, tbl_size, NULL);
        if (ltype == CHAR && rtype == INT) {
          fprintf(stderr, "Warning line %d: assigning 'int' to 'char' variable\n", node->lineno);
        }
        break;
      }
    }
  default:
    /* Pour tous les autres nœuds, parcourir les enfants */
    check_node_list(node->firstChild, func, table, tbl_size);
    break;
  }
}

/* Cherche un champ par nom dans un struct, récursivement dans les sous-structs */
static struct variable_info *find_field_recursive(struct definition_info *def,
                                                   const char *field_name) {
  if (!def || !field_name) return NULL;

  struct variable_info *field = def->liste_champs;
  while (field) {
    if (strcmp(field->identifiant, field_name) == 0)
      return field;

    // Si ce champ est lui-même un struct, chercher dedans
    if (field->type_nature == STRUCTURE && field->type_def) {
      struct variable_info *nested = find_field_recursive(field->type_def, field_name);
      if (nested) return nested;
    }

    field = field->next;
  }
  return NULL;
}
// get type expression
static enum type_nature get_expr_type(Node *expr, struct definition_info *func,
                             struct table_symbole *table, int tbl_size, struct definition_info **struct_def) {
  if (!expr)
    return INT;
  switch (expr->label) {
  case NODE_NUM:
    return INT;
  case NODE_CHARACTER:
    return CHAR;
  case NODE_IDENT:
    {
      struct variable_info *var = find_variable(expr->text, func, table, tbl_size);
      if (var) {
        if (struct_def) {
          *struct_def = var->type_def; // Set struct definition if requested
        }
        return var->type_nature;
      }
      return INT;
  }
  case NODE_ADDSUB:
  case NODE_DIVSTAR:
  case NODE_OR:
  case NODE_AND:
  case NODE_EQ:
  case NODE_ORDER:
    return INT;
  case NODE_UNARY:
  case NODE_NOT:
    return INT;
  case NODE_CALL_FUNCTION:
    {
      if (expr->firstChild && expr->firstChild->label == NODE_IDENT) {
        struct definition_info *def = find_in_table_symbole(expr->firstChild->text, table, tbl_size);
        if (def) {
          if(def->return_type == T_VOID) {
            fprintf(stderr, "Warning line %d: function '%s' returns void and cannot be used in an expression\n",
                    expr->firstChild->lineno, expr->firstChild->text);
            return INT; // Indicate error with a special type  
          }
          return def->return_type == T_CHAR ? CHAR : INT;
        }
      }
      return INT;
    }
  case NODE_DOT:
    {
      struct definition_info *left_struct = NULL;
      enum type_nature left_type = get_expr_type(expr->firstChild, func, table,
                                                tbl_size, &left_struct);
      if (left_type == STRUCTURE && left_struct) {
         Node *field_name = expr->firstChild->nextSibling;
        struct variable_info *found = find_field_recursive(left_struct, field_name->text);
        if (found) {
            if (struct_def) *struct_def = found->type_def;
            return found->type_nature;
        }
        fprintf(stderr, "Error line %d: struct '%s' has no field '%s'\n",
                expr->lineno, left_struct->identifiant, field_name->text);
    }
    return INT;
  }
  default:
    return INT; // Default type for unhandled cases
  }
}


/* Point d'entrée : parcourir toutes les fonctions et vérifier les déclarations */
void check_all_declarations(Node *root, struct table_symbole *table, int tbl_size) {
  if (!root) return;

  Node *current = root->firstChild;
  while (current) {
    if (current->label == NODE_DeclFoncts) {
      Node *func_node = current->firstChild;
      while (func_node) {
        if (func_node->label == NODE_DeclFonct) {
          /* Récupérer le nom de la fonction depuis EnTeteFonct */
          Node *enTete = func_node->firstChild;
          Node *typeNode = enTete->firstChild;
          Node *nameNode = typeNode->nextSibling;
          /* Cas struct retour : STRUCT IDENT(type) IDENT(nom) */
          if (typeNode->label == NODE_STRUCT) {
            nameNode = nameNode->nextSibling;
          }

          struct definition_info *func_def =
              find_in_table_symbole(nameNode->text, table, tbl_size);

          /* Parcourir le corps de la fonction */
          Node *corps = enTete->nextSibling;
          if (corps) {
            Node *suite = corps->firstChild;
            /* Sauter DeclVars pour aller à SuiteInstr */
            if (suite && suite->label == NODE_DeclVars) {
              suite = suite->nextSibling;
            }
            if (suite) {
              check_node_list(suite->firstChild, func_def, table, tbl_size);
            }
          }
        }
        func_node = func_node->nextSibling;
      }
    }
    current = current->nextSibling;
  }
}
