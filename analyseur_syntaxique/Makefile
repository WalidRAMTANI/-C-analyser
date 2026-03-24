EXEC = tpcas

SRC_DIR = src/
INC_DIR = inc/
COMPILER_SRC = ../compiler/src/
COMPILER_INC = ../compiler/include/

LEX_SRC = $(SRC_DIR)tpcas.l
YACC_SRC = $(SRC_DIR)tpcas.y
TREE_C = $(SRC_DIR)tree.c
TREE_H = $(INC_DIR)tree.h
LEX_C = $(SRC_DIR)tpcas.yy.c
YACC_C = $(SRC_DIR)tpcas.tab.c
YACC_H = $(INC_DIR)tpcas.tab.h

TREE_O = tree.o
YACC_O = tpcas.tab.o
LEX_O = tpcas.yy.o
COMPILER_O = compiler.o
INSTR_O = instruction.o
ASSEMBLER_EXEC = _anonymous
ASSEMBLER_SRC = _anonymous.asm
ASSEMBLER_OBJ = _anonymous.o

CC = gcc
CFLAGS = -Wall -Wextra -I$(INC_DIR) -I$(COMPILER_INC)

all: $(EXEC) $(ASSEMBLER_EXEC)

$(EXEC): $(YACC_O) $(LEX_O) $(TREE_O) $(COMPILER_O) $(INSTR_O)
	$(CC) $(CFLAGS) -o $@ $^ -ll

$(TREE_O): $(TREE_C) $(TREE_H)
	$(CC) $(CFLAGS) -c $(TREE_C) -o $@

$(YACC_O): $(YACC_C) $(TREE_H)
	$(CC) $(CFLAGS) -c $(YACC_C) -o $@

$(LEX_O): $(LEX_C) $(YACC_H)
	$(CC) $(CFLAGS) -c $(LEX_C) -o $@

$(COMPILER_O): $(COMPILER_SRC)compiler.c  $(COMPILER_INC)compiler.h
	$(CC) $(CFLAGS) -c $(COMPILER_SRC)compiler.c -o $@

$(INSTR_O): $(COMPILER_SRC)instruction.c  $(COMPILER_INC)compiler.h
	$(CC) $(CFLAGS) -c $(COMPILER_SRC)instruction.c -o $@


$(YACC_C) $(YACC_H): $(YACC_SRC)
	bison -d -o $(YACC_C) $(YACC_SRC)
	mv $(SRC_DIR)tpcas.tab.h $(YACC_H)

$(LEX_C): $(LEX_SRC) $(YACC_H)
	flex -o $@ $(LEX_SRC)

$(ASSEMBLER_SRC): $(EXEC)
	./$(EXEC) test/good/tp5.tpc

$(ASSEMBLER_OBJ): $(ASSEMBLER_SRC)
	nasm -f elf64 $< -o $@

$(ASSEMBLER_EXEC): $(ASSEMBLER_OBJ)
	gcc -no-pie -o $(ASSEMBLER_EXEC) $(ASSEMBLER_OBJ)  
clean:
	rm -f *.o $(EXEC) $(SRC_DIR)tpcas.tab.c $(SRC_DIR)tpcas.yy.c $(INC_DIR)tpcas.tab.h

mrproper: clean
	rm -f $(EXEC)
