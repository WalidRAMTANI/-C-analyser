%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "compiler.h"
int yylex();
extern int yylineno;
int yyerror(char *msg) {
    fprintf(stderr, "%d: %s\n", yylineno, msg);
    return 1;
}
    extern FILE *yyin;
Node *ptr = NULL;
%}

%union {
    Node *node;
    char *text;
}

%token <text> TYPE IDENT VOID NUM CHARACTER STRUCT
%token WHILE IF ELSE RETURN
%token <text> ORDER ADDSUB EQ DIVSTAR AND OR DOT
%type <node> Prog DeclVars Declarateurs DeclarateursStruct DeclFoncts DeclFonct EnTeteFonct Parametres ListTypVar Corps SuiteInstr Instr Exp TB FB M E T F Arguments ListExp LValue Value

%expect 1
%%

Prog
    : DeclVars DeclFoncts {
        $$ = makeNode(NODE_Prog, NULL);
        addChild($$, $1);
        addChild($$, $2);
        ptr = $$;
    }
    ;

DeclVars
    : DeclVars TYPE Declarateurs ';' {
        Node *var = makeNode(NODE_VAR_DECL, NULL);
        addChild(var, makeNode(NODE_TYPE, $2));
        addChild(var, $3);
        addChild($1, var);
        $$ = $1;
    }
    | DeclVars STRUCT IDENT Declarateurs ';' {
        Node *var = makeNode(NODE_VAR_DECL, NULL);
        addChild(var, makeNode(NODE_STRUCT, $2));
        addChild(var, makeNode(NODE_IDENT, $3));
        addChild(var, $4);
        addChild($1, var);
        $$ = $1;
    }
    | DeclVars STRUCT IDENT '{' DeclarateursStruct '}' ';' {
        Node *var = makeNode(NODE_STRUCT_DEF, NULL);
        addChild(var, makeNode(NODE_STRUCT, $2));
        addChild(var, makeNode(NODE_IDENT, $3));
        addChild(var, $5);
        addChild($1, var);
        $$ = $1;
    }
    | /* empty */ { $$ = makeNode(NODE_DeclVars, NULL); }
    ;

DeclarateursStruct
    : DeclarateursStruct TYPE Declarateurs ';' {
        Node *decl = makeNode(NODE_VAR_DECL, NULL);
        addChild(decl, makeNode(NODE_TYPE, $2));
        addChild(decl, $3);
        addChild($1, decl);
        $$ = $1;
    }
    | DeclarateursStruct STRUCT IDENT Declarateurs ';' {
        Node *decl = makeNode(NODE_VAR_DECL, NULL);
        addChild(decl, makeNode(NODE_STRUCT, $2));
        addChild(decl, makeNode(NODE_IDENT, $3));
        addChild(decl, $4);
        addChild($1, decl);
        $$ = $1;
    }
    | /* empty */ { $$ = makeNode(NODE_DeclarateursStruct, NULL); }
    ;

Declarateurs
    : Declarateurs ',' IDENT {
        addSibling($1, makeNode(NODE_IDENT, $3));
        $$ = $1;
    }
    | IDENT {
        $$ = makeNode(NODE_IDENT, $1);
    }
    ;

DeclFoncts
    : DeclFoncts DeclFonct { addChild($1, $2); $$ = $1; }
    | DeclFonct { $$ = makeNode(NODE_DeclFoncts, NULL); addChild($$, $1); }
    ;

DeclFonct
    : EnTeteFonct Corps {
        $$ = makeNode(NODE_DeclFonct, NULL);
        addChild($$, $1);
        addChild($$, $2);
    }
    ;

EnTeteFonct
    : TYPE IDENT '(' Parametres ')' {
        $$ = makeNode(NODE_EnTeteFonct, NULL);
        addChild($$, makeNode(NODE_TYPE, $1));
        addChild($$, makeNode(NODE_IDENT, $2));
        addChild($$, $4);
      }
    | VOID IDENT '(' Parametres ')' {
        $$ = makeNode(NODE_EnTeteFonct, NULL);
        addChild($$, makeNode(NODE_VOID, $1));
        addChild($$, makeNode(NODE_IDENT, $2));
        addChild($$, $4);
      }
    | STRUCT IDENT IDENT '(' Parametres ')' {
        $$ = makeNode(NODE_EnTeteFonct, NULL);
        addChild($$, makeNode(NODE_STRUCT, $1));
        addChild($$, makeNode(NODE_IDENT, $2));
        addChild($$, makeNode(NODE_IDENT, $3));
        addChild($$, $5);
      }
    ;

Parametres
    : VOID { $$ = makeNode(NODE_Parametres, NULL); addChild($$, makeNode(NODE_VOID, $1)); }
    | ListTypVar { $$ = $1; }
    | /* empty */ { $$ = makeNode(NODE_Parametres, NULL); }
    ;

ListTypVar
    : ListTypVar ',' TYPE IDENT {
        addChild($1, makeNode(NODE_TYPE, $3));
        addChild($1, makeNode(NODE_IDENT, $4));
        $$ = $1;
    }
    | ListTypVar ',' STRUCT IDENT IDENT {
        addChild($1, makeNode(NODE_STRUCT, $3));
        addChild($1, makeNode(NODE_IDENT, $4));
        addChild($1, makeNode(NODE_IDENT, $5));
        $$ = $1;
    }
    | TYPE IDENT {
        Node *list = makeNode(NODE_ListTypVar, NULL);
        addChild(list, makeNode(NODE_TYPE, $1));
        addChild(list, makeNode(NODE_IDENT, $2));
        $$ = list;
    }
    | STRUCT IDENT IDENT {
        Node *list = makeNode(NODE_ListTypVar, NULL);
        addChild(list, makeNode(NODE_STRUCT, $1));
        addChild(list, makeNode(NODE_IDENT, $2));
        addChild(list, makeNode(NODE_IDENT, $3));
        $$ = list;
    }
    ;

Corps
    : '{' DeclVars SuiteInstr '}' {
        $$ = makeNode(NODE_Corps, NULL);
        addChild($$, $2);
        addChild($$, $3);
    }
    ;

SuiteInstr
    : SuiteInstr Instr { addChild($1, $2); $$ = $1; }
    | /* empty */ { $$ = makeNode(NODE_SuiteInstr, NULL); }
    ;


LValue
    : Value DOT IDENT { 
        $$ = makeNode(NODE_DOT, NULL);
        addChild($$, $1);
        addChild($$, makeNode(NODE_IDENT, $3));
     }
    | IDENT {
        $$ = makeNode(NODE_IDENT, $1); 
    }
    ;
     
Value
    : IDENT '(' Arguments ')' {
        $$ = makeNode(NODE_IDENT, $1);
        addChild($$, $3);
    }
    
    | '(' Exp ')' 
    {
        $$ = $2;
    }
    | Value DOT IDENT {
        $$ = makeNode(NODE_DOT, NULL);
        addChild($$, $1);
        addChild($$, makeNode(NODE_IDENT, $3));
    }
    | IDENT{
        $$ = makeNode(NODE_IDENT, $1); 
    }
    ;
Instr
    : LValue '=' Exp ';' { $$ = makeNode(NODE_ASSIGN, NULL); addChild($$, $1); addChild($$, $3);  }
    | IF '(' Exp ')' Instr { $$ = makeNode(NODE_IF, NULL); addChild($$, $3); addChild($$, $5);}
    | IF '(' Exp ')' Instr ELSE Instr { $$ = makeNode(NODE_IF, NULL); addChild($$, $3); addChild($$, $5); addChild($$, $7);}
    | WHILE '(' Exp ')' Instr { $$ = makeNode(NODE_WHILE, NULL); addChild($$, $3); addChild($$, $5);  }
    | IDENT '(' Arguments ')' ';' { $$ = makeNode(NODE_CALL_FUNCTION, NULL); addChild($$, makeNode(NODE_IDENT, $1)); addChild($$, $3); }
    | RETURN Exp ';' { $$ = makeNode(NODE_RETURN, NULL); addChild($$, $2); }
    | RETURN ';' { $$ = makeNode(NODE_RETURN, NULL); }
    | '{' SuiteInstr '}' { $$ = $2; }
    | ';' { $$ = makeNode(NODE_EMPTY, NULL); }
    ;

Exp
    : Exp OR TB { $$ = makeNode(NODE_OR, $2); addChild($$, $1); addChild($$, $3); }
    | TB { $$ = $1; }
    ;

TB
    : TB AND FB { $$ = makeNode(NODE_AND, $2); addChild($$, $1); addChild($$, $3); }
    | FB { $$ = $1; }
    ;

FB
    : FB EQ M { $$ = makeNode(NODE_EQ, $2); addChild($$, $1); addChild($$, $3); }
    | M { $$ = $1; }
    ;

M
    : M ORDER E { $$ = makeNode(NODE_ORDER, $2); addChild($$, $1); addChild($$, $3); }
    | E { $$ = $1; }
    ;

E
    : E ADDSUB T { $$ = makeNode(NODE_ADDSUB, $2); addChild($$, $1); addChild($$, $3);  }
    | T { $$ = $1; }
    ;

T
    : T DIVSTAR F { $$ = makeNode(NODE_DIVSTAR, $2); addChild($$, $1); addChild($$, $3); }
    | F { $$ = $1; }
    ;

F
    : ADDSUB F { $$ = makeNode(NODE_UNARY, $1); addChild($$, $2); }
    | '!' F { $$ = makeNode(NODE_NOT, NULL); addChild($$, $2); }
    | '(' Exp ')' { $$ = $2; }
    | NUM { $$ = makeNode(NODE_NUM, $1); }
    | CHARACTER { $$ = makeNode(NODE_CHARACTER, $1); }
    | IDENT '(' Arguments ')' {  $$ = makeNode(NODE_CALL_FUNCTION, NULL); addChild($$, makeNode(NODE_IDENT, $1)); addChild($$, $3); }
    | LValue { $$ = $1; }
    ;


Arguments
    : ListExp { $$ = makeNode(NODE_Arguments, NULL); addChild($$, $1); }
    | /* empty */ { $$ = makeNode(NODE_Arguments, NULL); }
    ;

ListExp
    : Exp { $$ = makeNode(NODE_ListExp, NULL); addChild($$, $1); }
    | ListExp ',' Exp { addChild($$, $3); }
    ;

%%
    

void print_usage(char *prog_name) {
    printf("Usage: %s [OPTIONS] [FILE.tpc]\n", prog_name);
    printf("Analyseur syntaxique pour le langage TPC\n\n");
    printf("Options:\n");
    printf("  -t, --tree        Affiche l'arbre abstrait sur la sortie standard\n");
    printf("  -h, --help        Affiche cette aide et termine l'exécution\n\n");
    printf("\nValeurs de retour:\n");
    printf("  0  Aucune erreur lexicale ni syntaxique\n");
    printf("  1  Erreur lexicale ou syntaxique détectée\n");
    printf("  2+ Autres erreurs (ligne de commande, mémoire, etc.)\n");
}
    
int main(int argc, char **argv) {
    int show_tree = 0;
    int noption = 1;
    char *input_file = NULL;
    if(argc < 2){
        fprintf(stderr, "Utilisez -h ou --help pour plus d'informations\n");
        return 2;
    }
    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-help") == 0){
            print_usage(argv[0]);
            return 0;
        }
        if(strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "-tree") == 0){
            show_tree = 1
            ;
            noption++;
        }
    }
    if(noption < argc){
        input_file = argv[noption];
        yyin = fopen(input_file, "r");
        if (!yyin) {
            fprintf(stderr, "Erreur: impossible d'ouvrir le fichier '%s'\n", input_file);
            return 2;
        }
    }
    yylineno = 1;
    int result = yyparse();
    if (result != 0) {
        fprintf(stderr, "Analyse terminée \n");
        deleteTree(ptr);
        return 1;
        }
    if (show_tree) {
        printf("=== Arbre abstrait ===\n");
        generateTreePDF(ptr);
        printTree(ptr);
        
    }
    extern struct table_symbole globalTable[100];
    extern int size;
    // ----- - tp5 partie 2 -----
    //FILE *fp = fopen("_anonymous.asm", "w");
    FILE *fp = NULL; // Just for testing, we won't generate assembly yet
    // ----- - tp5 partie 2 -----
    fill_global_symbol_table(ptr, globalTable, fp);
    print_global_symbol_table(globalTable, size);
    // ----- TDC6 Exercice 1 : Vérification des déclarations -----
    check_all_declarations(ptr, globalTable, size);
    // ----- - tp5 partie 2 -----
    /*parcours_instruction(ptr, globalTable, fp);
    fprintf(fp, "mov rdi, format\n");
    fprintf(fp, "mov rsi, rbx\n");
    fprintf(fp, "xor rax, rax\n");
    fprintf(fp, "call printf\n");
    fprintf(fp, "mov rax, 60\n");
    fprintf(fp, "xor rdi, rdi\n");
    fprintf(fp, "syscall\n");
    fclose(fp);
    */
    // ----- - tp5 partie 3 -----
    deleteTree(ptr);
    return result;
}
