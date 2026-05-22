%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "compiler.h"
int yylex();
extern int yylineno;
int yyerror(char *msg);
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
    
int yyerror(char *msg) {
    fprintf(stderr, "%d: %s\n", yylineno, msg);
    return 1;
}

void print_usage(char *prog_name) {
    printf("Usage: %s [OPTIONS] [FILE.tpc]\n", prog_name);
    printf("Compilateur pour le langage TPC\n\n");
    printf("Options:\n");
    printf("  -t, --tree        Affiche l'arbre abstrait sur la sortie standard\n");
    printf("  -s, --symtabs     Affiche toutes les tables des symboles\n");
    printf("  -h, --help        Affiche cette aide et termine l'execution\n\n");
    printf("Valeurs de retour:\n");
    printf("  0  Aucune erreur\n");
    printf("  1  Erreur lexicale ou syntaxique\n");
    printf("  2  Erreur semantique\n");
    printf("  3  Autre erreur (ligne de commande, memoire, ...)\n");
}

int main(int argc, char **argv) {
    int show_tree = 0;
    int show_symtabs = 0;
    char *input_file = NULL;

    /* Parcourir les arguments */
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--tree") == 0) {
            show_tree = 1;
        } else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--symtabs") == 0) {
            show_symtabs = 1;
        } else if (argv[i][0] != '-') {
            /* Premier argument non-option = fichier source */
            input_file = argv[i];
        } else {
            fprintf(stderr, "Option inconnue: %s\n", argv[i]);
            return 3;
        }
    }
    printf("input: %s\n", input_file);
    /* Ouvrir le fichier source ou lire sur stdin */
    if (input_file != NULL) {
        yyin = fopen(input_file, "r");
        if (!yyin) {
            fprintf(stderr, "Erreur: impossible d'ouvrir le fichier '%s'\n", input_file);
            return 3;
        }
    }
    /* sinon yyin == NULL => yylex lit sur stdin par defaut */

    /* Determiner le nom du fichier cible */
    char output_file[512];
    if (input_file != NULL) {
        /* Remplacer l'extension .tpc par .asm */
        strncpy(output_file, input_file, sizeof(output_file) - 1);
        output_file[sizeof(output_file) - 1] = '\0';
        char *dot = strrchr(output_file, '.');
        if (dot != NULL)
            *dot = '\0';
        strncat(output_file, ".asm", sizeof(output_file) - strlen(output_file) - 1);
    } else {
        strncpy(output_file, "_anonymous.asm", sizeof(output_file) - 1);
    }

    yylineno = 1;
    int parse_result = yyparse();

    if (parse_result != 0) {
        /* Erreur lexicale ou syntaxique */
        if (ptr) deleteTree(ptr);
        if (input_file && yyin) fclose(yyin);
        return 1;
    }

    if (show_tree) {
        printf("=== Arbre abstrait ===\n");
        printTree(ptr);
        generateTreePDF(ptr);
    }

    /* Ouvrir le fichier assembleur cible */
    FILE *fp = fopen(output_file, "w");
    if (!fp) {
        fprintf(stderr, "Erreur: impossible de creer '%s'\n", output_file);
        deleteTree(ptr);
        if (input_file) fclose(yyin);
        return 3;
    }

    /* Remplir la table des symboles et generer le code */
    fill_global_symbol_table(ptr, globalTable, fp);

    if (show_symtabs) {
        print_global_symbol_table(globalTable, size);
    }

    /* Verifications semantiques */
    check_all_declarations(ptr, globalTable, size);

    /* Generation du code pour les instructions */
    parcours_instruction(ptr, globalTable, fp);

    fclose(fp);
    if (input_file && yyin) fclose(yyin);
    if (ptr) deleteTree(ptr);

    if (semantic_error)
        return 2;

    return 0;
}
