#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void  read_instructions(Node * func_node, struct table_symbole * globalTable, FILE *file);
void parcours_inst(Node *root, struct table_symbole *globalTable, FILE *file);
#endif