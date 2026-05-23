# Makefile - Compilateur TPC
# Projet Compilation L3 - 2025-2026
# Université Gustave Eiffel

EXEC = bin/tpcc

SRC_DIR = analyseur_syntaxique/src/
INC_DIR = analyseur_syntaxique/inc/
COMPILER_SRC = compiler/src/
COMPILER_INC = compiler/include/
OBJ_DIR = obj/

LEX_SRC = $(SRC_DIR)tpcas.l
YACC_SRC = $(SRC_DIR)tpcas.y
TREE_C = $(SRC_DIR)tree.c
TREE_H = $(INC_DIR)tree.h
LEX_C = $(SRC_DIR)tpcas.yy.c
YACC_C = $(SRC_DIR)tpcas.tab.c
YACC_H = $(INC_DIR)tpcas.tab.h

TREE_O = $(OBJ_DIR)tree.o
YACC_O = $(OBJ_DIR)tpcas.tab.o
LEX_O = $(OBJ_DIR)tpcas.yy.o
COMPILER_O = $(OBJ_DIR)compiler.o
INSTR_O = $(OBJ_DIR)instruction.o

CC = gcc
CFLAGS = -Wall -Wextra -I$(INC_DIR) -I$(COMPILER_INC)

all: $(EXEC)

$(EXEC): $(YACC_O) $(LEX_O) $(TREE_O) $(COMPILER_O) $(INSTR_O) | bin
	$(CC) $(CFLAGS) -o $@ $^ -ll

$(TREE_O): $(TREE_C) $(TREE_H) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(TREE_C) -o $@

$(YACC_O): $(YACC_C) $(TREE_H) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(YACC_C) -o $@

$(LEX_O): $(LEX_C) $(YACC_H) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(LEX_C) -o $@

$(COMPILER_O): $(COMPILER_SRC)compiler.c $(COMPILER_INC)compiler.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(COMPILER_SRC)compiler.c -o $@

$(INSTR_O): $(COMPILER_SRC)instruction.c $(COMPILER_INC)compiler.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $(COMPILER_SRC)instruction.c -o $@

$(YACC_C) $(YACC_H): $(YACC_SRC)
	bison -d -o $(YACC_C) $(YACC_SRC)
	mv $(SRC_DIR)tpcas.tab.h $(YACC_H)

$(LEX_C): $(LEX_SRC) $(YACC_H)
	flex -o $@ $(LEX_SRC)

bin:
	mkdir -p bin

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -f $(OBJ_DIR)*.o $(EXEC) $(SRC_DIR)tpcas.tab.c $(SRC_DIR)tpcas.yy.c $(INC_DIR)tpcas.tab.h *.dot tree.pdf _anonymous*

mrproper: clean
	rm -f $(EXEC) *.asm

.PHONY: all clean mrproper
