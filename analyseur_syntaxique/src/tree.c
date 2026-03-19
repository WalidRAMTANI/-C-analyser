/* tree.c */
#include "tree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int lineno = 0; /* from lexer */

static const char *StringFromLabel[] = {"Prog",
                                        "DeclVars",
                                        "VAR_DECL",
                                        "STRUCT_DECL",
                                        "STRUCT_DEF",
                                        "Declarateurs",
                                        "DeclarateursStruct",
                                        "DeclFoncts",
                                        "DeclFonct",
                                        "EnTeteFonct",
                                        "VOID",
                                        "TYPE",
                                        "Parametres",
                                        "ListTypVar",
                                        "Corps",
                                        "SuiteInstr",
                                        "Instr",
                                        "LValue",
                                        "Arguments",
                                        "ListExp",

                                        "STRUCT",
                                        "IF",
                                        "ELSE",
                                        "WHILE",
                                        "RETURN",
                                        "ASSIGN",
                                        "CALL_FUNCTION",
                                        "EMPTY",

                                        "OR",
                                        "AND",
                                        "EQ",
                                        "ORDER",
                                        "ADDSUB",
                                        "DIVSTAR",
                                        "UNARY",
                                        "NOT",

                                        "NUM",
                                        "CHARACTER",
                                        "IDENT",
                                        "DOT",
                                        "ARG_LIST",
                                        "Value"};

Node *makeNode(label_t label, char *text) {
  Node *node = malloc(sizeof(Node));
  if (!node) {
    printf("Run out of memory\n");
    exit(1);
  }
  node->label = label;
  /* take ownership of `text` (lexer allocated with strdup) */
  node->text = text;
  node->firstChild = node->nextSibling = NULL;
  node->lineno = lineno;
  return node;
}

void addSibling(Node *node, Node *sibling) {
  Node *curr = node;
  while (curr->nextSibling != NULL) {
    curr = curr->nextSibling;
  }
  curr->nextSibling = sibling;
}

void addChild(Node *parent, Node *child) {
  if (parent->firstChild == NULL) {
    parent->firstChild = child;
  } else {
    addSibling(parent->firstChild, child);
  }
}

void deleteTree(Node *node) {
  if (node->firstChild) {
    deleteTree(node->firstChild);
  }
  if (node->nextSibling) {
    deleteTree(node->nextSibling);
  }
  if (node->text)
    free(node->text);
  free(node);
}

void printTree(Node *node) {
  static bool rightmost[128];       // tells if node is rightmost sibling
  static int depth = 0;             // depth of current node
  for (int i = 1; i < depth; i++) { // 2502 = vertical line
    printf(rightmost[i] ? "    " : "\u2502   ");
  }
  if (depth > 0) { // 2514 = L form; 2500 = horizontal line; 251c = vertical
                   // line and right horiz
    printf(rightmost[depth] ? "\u2514\u2500\u2500 " : "\u251c\u2500\u2500 ");
  }
  printf("%s", StringFromLabel[node->label]);
  if (node->text)
    printf(" (%s)", node->text);
  printf("\n");
  depth++;
  for (Node *child = node->firstChild; child != NULL;
       child = child->nextSibling) {
    rightmost[depth] = (child->nextSibling) ? false : true;
    printTree(child);
  }
  depth--;
}

void write(Node *node, FILE *f) {
  fprintf(f, "  node_%p [label=\"%s", (void *)node,
          StringFromLabel[node->label]);

  if (node->text)
    fprintf(f, "\\n(%s)", node->text);

  fprintf(f, "\"];\n");

  for (Node *child = node->firstChild; child; child = child->nextSibling) {
    fprintf(f, "  node_%p -> node_%p;\n", (void *)node, (void *)child);
    write(child, f);
  }
}
void generateTreePDF(Node *root) {
  if (!root)
    return;

  FILE *f = fopen("tree.dot", "w");
  if (!f) {
    perror("fopen");
    return;
  }

  fprintf(f, "digraph AST {\n");
  fprintf(f, "  node [shape=box, fontname=\"Courier\"];\n");
  fprintf(f, "  edge [fontname=\"Courier\"];\n\n");

  write(root, f);

  fprintf(f, "}\n");
  fclose(f);

  // Try to generate PDF using dot command
  int ret = system("which dot > /dev/null 2>&1");
  if (ret == 0) {
    // dot is available
    int pdf_ret = system("dot -Tpdf tree.dot -o tree.pdf");
    if (pdf_ret == 0) {
      printf("PDF generated successfully: tree.pdf\n");
    } else {
      fprintf(stderr, "Warning: Failed to generate PDF from tree.dot\n");
      fprintf(stderr, "The tree.dot file was generated successfully.\n");
    }
  } else {
    fprintf(stderr, "Warning: 'dot' command not found. Graphviz is not installed.\n");
    fprintf(stderr, "The tree.dot file was generated successfully.\n");
    fprintf(stderr, "To generate a PDF, install Graphviz:\n");
    fprintf(stderr, "  macOS: brew install graphviz\n");
    fprintf(stderr, "  Ubuntu/Debian: sudo apt-get install graphviz\n");
  }
}

