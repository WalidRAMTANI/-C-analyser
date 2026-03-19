# TPC Compiler - Assembly Generation & Execution

## Overview

This project implements a TPC (Tiny Pascal/C) language compiler that:
1. **Parses** TPC source files (`.tpc`)
2. **Generates** x86-64 assembly code (`_anonymous.asm`)
3. **Compiles** assembly to executable binaries
4. **Executes** the generated code

## Architecture

```
TPC Source Code (.tpc)
        ↓
   [Lexical Analysis - Flex]
        ↓
   [Syntax Analysis - Bison]
        ↓
   [Abstract Syntax Tree]
        ↓
   [Code Generation]
        ↓
   x86-64 Assembly (.asm)
        ↓
   [NASM Assembler]
        ↓
   Object File (.o)
        ↓
   [GCC Linker]
        ↓
   Executable Program
        ↓
   [Execution & Result]
```

## Quick Start

### On macOS (ARM64)
```bash
cd analyseur_syntaxique
make
./tpcas test/good/tp5.tpc -t  # View AST
cat _anonymous.asm             # View generated assembly
# Note: macOS ARM64 cannot directly run x86-64 code
```

### On Linux or GitHub Codespaces (x86-64)
```bash
cd analyseur_syntaxique
make
./tpcas test/good/tp5.tpc
./compile_linux.sh _anonymous.asm
```

## Files Structure

```
analyseur_syntaxique/
├── tpcas                    # Main parser executable
├── _anonymous.asm          # Generated x86-64 assembly
├── tree.pdf               # AST visualization (when -t flag used)
├── compile_linux.sh       # Script to compile assembly on Linux
├── quick_compile.sh       # Quick start script
├── Makefile              # Build configuration
├── src/
│   ├── tpcas.l          # Lexer (Flex)
│   ├── tpcas.y          # Parser (Bison)
│   └── tree.c           # AST manipulation
└── test/good/           # Test TPC programs
    ├── tp5.tpc          # Simple program example
    ├── 01_minimal.tpc
    ├── 02_global_vars.tpc
    └── ...

compiler/
├── src/
│   ├── compiler.c       # Symbol table & code generation
│   └── instruction.c    # Instruction generation
└── include/
    └── compiler.h       # Headers
```

## Building the Project

### Prerequisites
- GCC compiler
- Make build system
- Flex (lexical analyzer)
- Bison (parser generator)
- NASM (x86-64 assembler) - for Linux/Codespaces
- Graphviz (optional, for AST visualization)

### Build Steps
```bash
cd analyseur_syntaxique
make clean      # Remove old build files
make           # Build the project
```

## Using the Parser

### Basic Usage
```bash
./tpcas input.tpc              # Parse and generate assembly
./tpcas input.tpc -t           # Parse, generate AST PDF, and assembly
./tpcas input.tpc -h           # Show help
```

### Output Files
- `_anonymous.asm` - Generated x86-64 assembly code
- `tree.dot` - Graphviz representation of AST (text format)
- `tree.pdf` - Visual AST (requires Graphviz)

## Compiling Generated Assembly

### On Linux/Codespaces (Recommended)
```bash
./compile_linux.sh _anonymous.asm
```

### Manual Steps
```bash
# Step 1: Assemble (NASM -> Object file)
nasm -f elf64 _anonymous.asm -o _anonymous.o

# Step 2: Link (Object file -> Executable)
gcc _anonymous.o -o _anonymous

# Step 3: Run
./_anonymous
echo $?  # Check exit code
```

## Example: Complete Workflow

```bash
# 1. Create a TPC program
cat > hello.tpc << 'EOF'
int main(void) {
    int x;
    x = 5;
    return 0;
}
EOF

# 2. Parse and generate assembly
./tpcas hello.tpc

# 3. View generated assembly
cat _anonymous.asm

# 4. Compile assembly (on Linux/Codespaces)
./compile_linux.sh _anonymous.asm

# 5. Check the result
echo "Exit code: $?"
```

## Testing

Run tests on various TPC programs:

```bash
# Minimal program
./tpcas test/good/01_minimal.tpc
./compile_linux.sh _anonymous.asm

# Program with global variables
./tpcas test/good/02_global_vars.tpc
./compile_linux.sh _anonymous.asm

# Program with structures
./tpcas test/good/03_simple_struct.tpc
./compile_linux.sh _anonymous.asm
```

Check `test/good/` for more examples.

## GitHub Codespaces Setup

For the easiest cross-platform experience:

1. Go to: https://github.com/WalidRAMTANI/-C-analyser
2. Click **Code** → **Codespaces** → **Create codespace on main**
3. Wait for environment to load
4. In terminal:
   ```bash
   cd analyseur_syntaxique
   make
   ./quick_compile.sh test/good/tp5.tpc
   ```

See `CODESPACES_GUIDE.md` for detailed setup.

## Symbol Table Generation

The compiler also generates a comprehensive symbol table:

```
+-----------+----------+--------+--------+----------+
| Identifier| Kind     | Type   | Offset | Size/Ret |
+-----------+----------+--------+--------+----------+
| main      | FUNC     | int    | -      | Stk: 4   |
| x         | LOCAL    | int    | 0      |          |
+-----------+----------+--------+--------+----------+
```

## Assembly Code Generation

The instruction.c module generates x86-64 assembly:

- **Variable assignments**: `mov` instructions
- **Arithmetic operations**: `add`, `sub`, `mul`, `div`
- **Function returns**: Proper register setup and return
- **Control flow**: Conditional jumps and labels

## Troubleshooting

### macOS Build Issues
- Use GitHub Codespaces for x86-64 assembly support
- Or follow the Linux VM setup guide

### Assembly Compilation Errors
```bash
# Check NASM syntax
nasm -f elf64 _anonymous.asm

# View the problematic assembly
cat _anonymous.asm | head -20
```

### Missing Dependencies
```bash
# Linux/Codespaces
sudo apt-get update
sudo apt-get install build-essential flex bison nasm

# macOS
brew install flex bison nasm graphviz
```

## Further Development

Potential improvements:
- [ ] Support more operators and expressions
- [ ] Implement function calls
- [ ] Add loop support
- [ ] Generate optimized assembly
- [ ] Support more data types
- [ ] Error recovery and reporting

## References

- [x86-64 ABI](https://github.com/hjl-tools/x86-psABI/wiki/x86-64-psABI-1.0.pdf)
- [NASM Manual](https://www.nasm.us/doc/)
- [System V AMD64 ABI](https://gitlab.com/x86-psABIs/x86-64-ABI)
- [Linux Syscalls](https://syscalls.kernelgsl.com/)

## License

University project for Compilation course.

---

**Happy Compiling!** 🚀
