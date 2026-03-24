#include "compiler.h"
#include <stdio.h>

void  read_instructions(Node * func_node, struct table_symbole * globalTable, FILE *file){
    if (!func_node || !globalTable || !file)
        return;
    
    if (!func_node->firstChild)
        return;
    
    Node *corps = func_node->firstChild->nextSibling;
    if (!corps)
        return;
    
    Node *suite_instr = corps->firstChild;
    
    if(suite_instr && suite_instr->label == NODE_DeclVars) {
        suite_instr = suite_instr->nextSibling;
    }
    
    if (!suite_instr)
        return;
    
    Node *instruction = suite_instr->firstChild;
    while (instruction) {
        fprintf(file, "; Processing instruction at line %d\n", instruction->lineno);
        if(instruction->label == NODE_ASSIGN) {
            fprintf(file, "; ASSIGN\n");
            if(instruction->firstChild && instruction->firstChild->nextSibling) {
                Node *varNode = instruction->firstChild;
                Node *exprNode = instruction->firstChild->nextSibling;
                fprintf(file, "push %s\n", exprNode->firstChild->nextSibling->text ? exprNode->firstChild->nextSibling->text : "unknown");
                fprintf(file, "push %s\n", exprNode->firstChild->text ? exprNode->firstChild->text : "unknown");
                fprintf(file, "; Expression evaluation would go here\n");
                fprintf(file, "pop rbx\n");
                fprintf(file, "pop rax\n");
                fprintf(file, "; After expression evaluation, we would have the value in rax and the variable address in rbx\n");
                fprintf(file, "sub rbx, rax\n");
            }
        }
        else if(instruction->label == NODE_RETURN) {
            fprintf(file, "; Return statement found\n");
            // Handle return
            if(instruction->firstChild) {
                fprintf(file, "mov rax, %s\n", instruction->firstChild->text ? instruction->firstChild->text : "0");
            } else {
                fprintf(file, "xor rax, rax\n");
            }
        }
        instruction = instruction->nextSibling;
    }
}

void parcours_instruction(Node *root, struct table_symbole *globalTable, FILE *file) {
  if (!root || !globalTable)
    return;

  Node *current = root->firstChild;
  while (current) {
    if (current->label == NODE_DeclFoncts) {
      Node *func_node = current->firstChild;
      while (func_node) {
        if (func_node->label == NODE_DeclFonct) {
          // lire les instructions de la fonction et les ecrire dans le fichier anonymous
          read_instructions(func_node, globalTable, file);
        }
        func_node = func_node->nextSibling;
      }
    }
    current = current->nextSibling;
  }
}
