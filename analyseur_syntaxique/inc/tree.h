/* tree.h */

typedef enum {
  NODE_Prog,
  NODE_DeclVars,
  NODE_VAR_DECL,
  NODE_STRUCT_DECL,
  NODE_STRUCT_DEF,
  NODE_Declarateurs,
  NODE_DeclarateursStruct,
  NODE_DeclFoncts,
  NODE_DeclFonct,
  NODE_EnTeteFonct,
  NODE_VOID,
  NODE_TYPE,
  NODE_Parametres,
  NODE_ListTypVar,
  NODE_Corps,
  NODE_SuiteInstr,
  NODE_Instr,
  NODE_LValue,
  NODE_Arguments,
  NODE_ListExp,

  NODE_STRUCT,
  NODE_IF,
  NODE_ELSE,
  NODE_WHILE,
  NODE_RETURN,
  NODE_ASSIGN, /* '=' token */
  NODE_CALL_FUNCTION,
  NODE_EMPTY,
  NODE_OR,
  NODE_AND,
  NODE_EQ,
  NODE_ORDER,
  NODE_ADDSUB,
  NODE_DIVSTAR,
  NODE_UNARY,
  NODE_NOT,

  NODE_NUM,
  NODE_CHARACTER,
  NODE_IDENT,
  NODE_DOT,
  NODE_ARG_LIST
} label_t;

typedef struct Node {
  label_t label;
  char *text;
  struct Node *firstChild, *nextSibling;
  int lineno;
} Node;

/* makeNode takes ownership of `text` (caller must not free it) */
Node *makeNode(label_t label, char *text);
void addSibling(Node *node, Node *sibling);
void addChild(Node *parent, Node *child);
void deleteTree(Node *node);
void printTree(Node *node);
void generateTreePDF(Node *root);

#define FIRSTCHILD(node) node->firstChild
#define SECONDCHILD(node) node->firstChild->nextSibling
#define THIRDCHILD(node) node->firstChild->nextSibling->nextSibling
