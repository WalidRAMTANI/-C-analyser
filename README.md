# TPC Parser & Symbol Table Generator

A robust lexical and syntax analyzer for the **TPC (Tiny Pascal/C)** language, developed as part of a Compilation course. This tool parses TPC source files, builds an Abstract Syntax Tree (AST), and generates a comprehensive global symbol table tracking variables, functions, and structures.

## 🚀 Features

- **Lexical Analysis**: Built with **Flex** to tokenize TPC source code.
- **Syntax Analysis**: Built with **Bison (LALR parser)** to validate language grammar.
- **AST Generation**: Construct a detailed Abstract Syntax Tree representing the program structure.
- **Symbol Table**: Automaticaly generates a global symbol table with:
    - Variable types and memory offsets.
    - Function return types, parameters, and stack-frame sizes.
    - Structure definitions and member offsets.
- **Visualization**: Supports AST visualization via Graphviz (`.dot` file generation).

## 📁 Project Structure

```text
.
├── analyseur_syntaxique/   # Main parser implementation
│   ├── inc/                # Header files (tree.h, str.h, etc.)
│   ├── src/                # source files (tpcas.l, tpcas.y, tree.c)
│   ├── test/               # test suite (.tpc files)
│   └── Makefile            # Build configuration
├── compiler/               # Core logic for symbol table management
│   ├── include/            # compiler.h
│   └── src/                # compiler.c (Semantic analysis & Table filling)
└── README.md               # This file
```

## 🛠 Prerequisites

Ensure you have the following installed on your system:
- **GCC** (C Compiler)
- **Flex** (Lexical Analyzer Generator)
- **Bison** (Parser Generator)
- **Make** (Build Tool)
- **Graphviz** (Optional, for AST visualization)

## 🔨 Building the Project

Navigate to the `analyseur_syntaxique` directory and run:

```bash
cd analyseur_syntaxique
make
```

This will generate the `tpcas` executable.

## 📖 Usage

Run the parser on a TPC source file:

```bash
./tpcas [OPTIONS] [FILE.tpc]
```

### Options:
- `-t` or `--tree`: Display the Abstract Syntax Tree (AST) and generate a PDF visualization (if Graphviz is available).
- `-h` or `--help`: Show the help menu.

### Example:
```bash
./tpcas -t test/good/03_simple_struct.tpc
```

## 📝 TPC Language Syntax

The parser supports:
- **Types**: `int`, `char`, and user-defined `struct`.
- **Functions**: Declarations with `void` or typed returns, parameters, and local variables.
- **Control Flow**: `if`, `else`, `while` loops.
- **Structures**: Definition and member access using dot notation (`p.x`).
- **Operators**: Arithmetic (`+`, `-`, `*`, `/`), Logical (`&&`, `||`, `!`), and Relational (`==`, `!=`, `<`, `>`).

### Sample Code (`example.tpc`):
```c
struct Point {
    int x;
    int y;
};

int main(void) {
    struct Point p;
    p.x = 10;
    if (p.x > 0) {
        return 1;
    }
    return 0;
}
```

## 📊 Symbol Table Output

The tool generates a detailed table similar to:
```text
+---------------------------------------------------------------------------+
|                            GLOBAL SYMBOL TABLE                            |
+----------------------+------------+------------+-----------+---------------+
| Identifier           | Kind       | Type       | Offset    | Size/Ret      |
+----------------------+------------+------------+-----------+---------------+
| Point                | STRUCT     |            | -         | Sz: 8         |
|   x                  | FIELD      | int        | 0         |               |
|   y                  | FIELD      | int        | 4         |               |
+----------------------+------------+------------+-----------+---------------+
| main                 | FUNC       | int        | -         | Stk: 8        |
|   p                  | LOCAL      | Point      | 0         |               |
+----------------------+------------+------------+-----------+---------------+
```

## 🤝 Credits

Developed as part of the University Compilation course.
# -C-analyser
