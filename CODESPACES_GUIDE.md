# GitHub Codespaces Setup Guide

## What is GitHub Codespaces?

GitHub Codespaces is a cloud-based development environment hosted by GitHub. It provides:
- **Free Linux environment** (Ubuntu 22.04)
- **x86-64 CPU architecture** (compatible with NASM assembly)
- **Automatic setup** via `.devcontainer/devcontainer.json`
- **Pre-configured tools** (GCC, NASM, Flex, Bison, Graphviz)
- **No local setup required**

## Quick Start (3 Steps)

### Step 1: Open in Codespaces
1. Go to: https://github.com/WalidRAMTANI/-C-analyser
2. Click the green **Code** button
3. Select **Codespaces** tab
4. Click **Create codespace on main**
5. Wait ~2 minutes for environment setup

### Step 2: Build the Project
```bash
cd analyseur_syntaxique
make clean
make
```

### Step 3: Compile and Run
```bash
# Parse a TPC program
./tpcas test/good/tp5.tpc

# Compile the generated assembly
./compile_linux.sh _anonymous.asm

# Or use the quick script
./quick_compile.sh test/good/tp5.tpc
```

## Understanding the Environment

### What Gets Installed?
The `.devcontainer/devcontainer.json` automatically installs:

```bash
# Build tools
build-essential          # GCC, Make, etc.
flex                     # Lexical analyzer
bison                    # Parser generator

# Assembly tools
nasm                     # x86-64 Assembler

# Visualization
graphviz                 # PDF generation (dot command)

# Development tools
git                      # Version control
nano vim emacs          # Text editors
```

### Container Specs
- **OS**: Ubuntu 22.04 LTS
- **CPU**: x86-64 (AMD64)
- **Memory**: 4 GB RAM
- **Storage**: 32 GB disk

## Architecture: macOS vs Codespaces

| Aspect | macOS (ARM64) | Codespaces (x86-64) |
|--------|---------------|-------------------|
| CPU | Apple Silicon | x86-64 (AMD/Intel) |
| Assembly | ARM64 compatible | x86-64 compatible |
| NASM `-f` | macho64 (won't work) | elf64 (works!) |
| Linking | Apple ld | GNU ld |
| Syscalls | Apple specific | Linux syscalls |
| Status | Parse only | Full pipeline ✅ |

## Using the Scripts

### `./tpcas` - The Parser
```bash
# Generate assembly from TPC file
./tpcas input.tpc

# Generate assembly + create AST PDF
./tpcas input.tpc -t

# Show help
./tpcas -h
```

**Output files:**
- `_anonymous.asm` - x86-64 assembly code
- `tree.pdf` - AST visualization (if -t used)

### `./compile_linux.sh` - Compile Assembly
```bash
# Compile the generated assembly
./compile_linux.sh _anonymous.asm

# Or manually:
nasm -f elf64 _anonymous.asm -o _anonymous.o
gcc _anonymous.o -o _anonymous
./_anonymous
echo "Exit code: $?"
```

### `./quick_compile.sh` - Full Pipeline
```bash
# One command to do everything:
# Parse → Generate Assembly → Compile → Run
./quick_compile.sh test/good/tp5.tpc
```

## Complete Workflow Example

```bash
# 1. In Codespaces, open terminal
cd analyseur_syntaxique

# 2. Build the project (first time only)
make

# 3. Create a test TPC program
cat > test_program.tpc << 'EOF'
int main(void) {
    int x;
    x = 42;
    return x;
}
EOF

# 4. Parse and generate assembly
./tpcas test_program.tpc

# 5. View the generated assembly
cat _anonymous.asm

# 6. Compile the assembly
nasm -f elf64 _anonymous.asm -o test.o
gcc test.o -o test_program

# 7. Run the program
./test_program
echo "Exit code: $?"        # Should print: 42
```

## Testing with Provided Examples

The project includes test files in `test/good/`:

```bash
# Test 1: Minimal program
./tpcas test/good/01_minimal.tpc
./compile_linux.sh _anonymous.asm

# Test 2: Global variables
./tpcas test/good/02_global_vars.tpc
./compile_linux.sh _anonymous.asm

# Test 3: Structures
./tpcas test/good/03_simple_struct.tpc
./compile_linux.sh _anonymous.asm

# Test 4: Function calls
./tpcas test/good/14_function_calls.tpc
./compile_linux.sh _anonymous.asm
```

## Viewing Generated Assembly

After running `./tpcas input.tpc`:

```bash
# View the assembly code
cat _anonymous.asm

# First few lines:
head -20 _anonymous.asm

# Search for specific instructions
grep "mov" _anonymous.asm

# Count instructions
wc -l _anonymous.asm
```

## Viewing the AST

Generate PDF visualization of the Abstract Syntax Tree:

```bash
# Generate AST and assembly
./tpcas input.tpc -t

# View the PDF (Codespaces has a built-in viewer)
# Or download it and view locally

# Or view the raw dot format
cat tree.dot
```

## Troubleshooting in Codespaces

### Issue: `make` fails with compiler errors

**Solution:**
```bash
# Clean and rebuild
make clean
make -B

# Check gcc version
gcc --version

# Check if flex/bison are installed
flex --version
bison --version
```

### Issue: NASM fails with "invalid output format"

**This shouldn't happen in Codespaces**, but if it does:
```bash
# Wrong format (macOS):
nasm -f macho64 file.asm  # ❌ Wrong

# Correct format (Linux/Codespaces):
nasm -f elf64 file.asm    # ✅ Correct
```

### Issue: Compilation works but program doesn't run

**Check exit code:**
```bash
./program
echo $?     # Should show the return value

# Add debug output:
./program
echo "Exit status: $?"
```

### Issue: "Permission denied" when running script

**Fix permissions:**
```bash
chmod +x quick_compile.sh
chmod +x compile_linux.sh
./quick_compile.sh test/good/tp5.tpc
```

## Terminal Commands Reference

```bash
# Project structure
ls -la                          # List files
tree analyseur_syntaxique       # Tree view

# Building
cd analyseur_syntaxique
make                           # Build parser
make clean                     # Clean build files

# Parsing/Assembly generation
./tpcas input.tpc              # Generate assembly
./tpcas input.tpc -t           # Generate assembly + PDF

# Viewing generated files
cat _anonymous.asm             # View assembly
cat tree.dot                   # View AST (text)
file tree.pdf                  # Check PDF

# Assembly compilation
nasm -f elf64 _anonymous.asm -o _anonymous.o    # Assemble
gcc _anonymous.o -o _anonymous                  # Link
./_anonymous                                    # Run

# Exit codes
./program && echo "Success" || echo "Failed"
./program; echo "Exit code: $?"

# Cleanup
rm _anonymous.o _anonymous *.o              # Remove compiled files
```

## Key Differences from macOS

1. **Assembler format**: `-f elf64` instead of `-f macho64`
2. **Linker**: GNU ld instead of Apple ld
3. **Syscalls**: Linux syscalls (exit = 60) instead of macOS (exit = 0x2000001)
4. **Libraries**: Standard glibc instead of Apple libraries

## Working with Files in Codespaces

### Download Files to Local Machine
```bash
# File → Download (built-in Codespaces feature)
# Or use git to push changes to GitHub
```

### Push Changes to GitHub
```bash
git add .
git commit -m "Generated assembly for program X"
git push origin main
```

### Edit in VS Code Web
- Codespaces opens VS Code in browser
- Full editing experience
- Git integration built-in

## Next Steps

1. **Build the project**: `cd analyseur_syntaxique && make`
2. **Run the quick script**: `./quick_compile.sh test/good/tp5.tpc`
3. **View generated assembly**: `cat _anonymous.asm`
4. **Test with your own TPC files**
5. **Explore the code** in the editor

## Additional Resources

- [GitHub Codespaces Documentation](https://docs.github.com/en/codespaces)
- [NASM Manual](https://www.nasm.us/doc/)
- [x86-64 ABI](https://github.com/hjl-tools/x86-psABI/wiki/x86-64-psABI-1.0.pdf)
- [Linux System Calls](https://syscalls.kernelgsl.com/)

## Free Usage

GitHub provides:
- **120 core hours per month** (free)
- **15 GB storage per month** (free)
- Perfect for this project!

---

**Ready to compile? Start with Step 1!** 🚀
