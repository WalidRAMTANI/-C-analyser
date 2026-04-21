#include "compiler.h"
#include <stdio.h>

void calculate_expr(Node *exprNode, FILE *file){
    if(exprNode->firstChild) {
        fprintf(file, "push %s\n", exprNode->firstChild->nextSibling->text);
        if(exprNode->firstChild->nextSibling->label == NODE_IDENT) {
            fprintf(file, "push %s\n", exprNode->firstChild->text);
        }else {
            calculate_expr(exprNode->firstChild, file);
            fprintf(file, "push rax\n");
        }
        fprintf(file, "pop rbx\n");
        fprintf(file, "pop rax\n");
        if(exprNode->label == NODE_ADDSUB) {
            fprintf(file, "%s rax, rbx\n", exprNode->text[0] == '+' ? "add" : "sub");
        } else if(exprNode->label == NODE_DIVSTAR) {
            fprintf(file, "%s rax, rbx\n", exprNode->text[0] == '*' ? "imul" : "xor rdx, rdx\nidiv rbx");
        } else if(exprNode->label == NODE_OR) {
            fprintf(file, "or rax, rbx\n");
        } else if(exprNode->label == NODE_AND) {
            fprintf(file, "and rax, rbx\n");
        } else if(exprNode->label == NODE_EQ) {
            fprintf(file, "cmp rax, rbx\n");
            fprintf(file, "sete al\n");
            fprintf(file, "movzx rax, al\n");
        } else if(exprNode->label == NODE_ORDER) {
            fprintf(file, "cmp rax, rbx\n");
            if(exprNode->text[0] == '<') {
                fprintf(file, "setl al\n");
            } else if(exprNode->text[0] == '>') {
                fprintf(file, "setg al\n");
            } else if(exprNode->text[0] == '!' && exprNode->text[1] == '=') {
                fprintf(file, "setne al\n");
            }
            fprintf(file, "movzx rax, al\n");
        }
    } else {
        // check if it's a variable or a number
        fprintf(file, "mov rbx, %s\n", exprNode->text);
    }
}

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
                // treat global variables only for now, local variables will be handled in the next part of the project
                 struct variable_info *var_info = find_variable(varNode->text, NULL, globalTable, size);
                if(var_info && var_info->container == NULL) {
                    if(exprNode->firstChild) {
                        fprintf(file, "push %s\n", exprNode->firstChild->nextSibling->text);
                        fprintf(file, "push %s\n", exprNode->firstChild->text);
                        fprintf(file, "pop rbx\n");
                        fprintf(file, "pop rax\n");
                        fprintf(file, "sub rbx, rax\n");
                    }else {
                        fprintf(file, "mov eax, %s\n", exprNode->text);
                        fprintf(file, "mov dword [%s], eax\n", varNode->text);
                    }
                
                }
            }
        }
        // return statement
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
