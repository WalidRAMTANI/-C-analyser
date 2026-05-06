# Test Files for TPC Compiler

## How to Run Tests

Save each test file in your `test/` directory, then run:

```bash
./bin/tpcas < test/test1.txt
./bin/tpcas < test/test2.txt
# etc.
```

## Test Files Description

### test1.txt - Simple Variable Declarations
- Basic variable declarations with different types
- Simple main function
- Tests: variable lists, basic function structure

### test2.txt - Functions with Parameters
- Function declarations with parameters
- Function calls with arguments
- Tests: parameter lists, function calls, expressions

### test3.txt - Control Structures
- If-else statements
- While loops
- Relational operators (>, <)
- Tests: control flow, nested expressions, arithmetic operators

### test4.txt - Structs
- Struct definition with members
- Struct variable declarations
- Member access using dot notation (.)
- Tests: struct syntax, member access, struct variables

### test5.txt - Complex Expressions
- Logical operators (&&, ||)
- Comparison operators (==, >, <)
- Arithmetic operators (+, -, *, /)
- Nested conditionals
- Tests: operator precedence, complex boolean expressions

### test6.txt - Comprehensive Test
- Combines all features
- Multiple structs
- Multiple functions
- Nested blocks
- Complex control flow
- Tests: complete program structure

### test_empty.txt - Empty Functions
- Void return type
- Void parameters
- Empty statement (;)
- Tests: void keyword, empty statements

### test_error.txt - Syntax Error Test
- Contains a syntax error (missing semicolon)
- Tests: error reporting and line numbers
- Expected: SYNTAX ERROR message

## Expected Output

For valid programs, you should see a tree structure like:

```
Prog
├── DeclVars
│   └── VAR_DECL
│       ├── TYPE
│       └── IDENT
└── DeclFoncts
    └── DeclFonct
        ├── EnTeteFonct
        │   ├── TYPE
        │   ├── IDENT
        │   └── Parametres
        └── Corps
            └── ...
```

For test_error.txt, you should see:
```
SYNTAX ERROR line 4: syntax error
```

## Quick Test Command

To run all tests at once:

```bash
for test in test/test*.txt; do
    echo "=== Testing $test ==="
    ./bin/tpcas < "$test"
    echo ""
done
```
