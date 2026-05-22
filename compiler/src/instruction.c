/*
 * instruction.c — Génération de code NASM pour le compilateur TPC
 *
 * Ce fichier parcourt l'AST (après remplissage de la table des symboles)
 * et émet le code assembleur NASM (syntaxe ELF64, conventions AMD64).
 *
 * Architecture du fichier .asm produit :
 *   section .bss    → variables globales  (émis par compiler.c)
 *   section .text   → fonctions I/O + fonctions utilisateur + _start
 *
 * Conventions d'appel AMD64 utilisées :
 *   - Arguments : rdi, rsi, rdx, rcx, r8, r9 (6 premiers)
 *   - Valeur de retour : rax
 *   - Registres sauvegardés par l'appelé : rbp, rbx, r12-r15
 *   - Pile alignée sur 16 octets avant chaque call
 *
 * Pour les expressions, on utilise la pile comme accumulateur temporaire :
 *   eval(gauche) → push rax → eval(droite) → pop rbx → op rax, rbx
 */

#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================================================
 *  Compteur global pour générer des étiquettes uniques
 * ========================================================= */
static int label_counter = 0;
static int new_label(void) { return label_counter++; }

/* =========================================================
 *  Fonctions I/O intégrées écrites en NASM
 * ========================================================= */
static void emit_builtin_io(FILE *fp) {
    fprintf(fp,
        "; ===== Built-in I/O =====\n"
        "\n"
        "; putchar(char c) : affiche le caractère passé dans rdi\n"
        "putchar:\n"
        "    push    rbp\n"
        "    mov     rbp, rsp\n"
        "    sub     rsp, 16\n"
        "    mov     byte [rbp-1], dil\n"
        "    mov     rax, 1\n"
        "    mov     rdi, 1\n"
        "    lea     rsi, [rbp-1]\n"
        "    mov     rdx, 1\n"
        "    syscall\n"
        "    leave\n"
        "    ret\n"
        "\n"
        "; putint(int i) : affiche l'entier passé dans rdi suivi d'un newline\n"
        "putint:\n"
        "    push    rbp\n"
        "    mov     rbp, rsp\n"
        "    sub     rsp, 32\n"
        "    mov     rax, rdi\n"
        "    lea     r9, [rbp-21]\n"
        "    mov     byte [r9], 10\n"
        "    dec     r9\n"
        "    test    rax, rax\n"
        "    jns     .putint_pos\n"
        "    neg     rax\n"
        "    mov     r10, 1\n"
        "    jmp     .putint_loop\n"
        ".putint_pos:\n"
        "    mov     r10, 0\n"
        ".putint_loop:\n"
        "    xor     rdx, rdx\n"
        "    mov     rcx, 10\n"
        "    div     rcx\n"
        "    add     dl, '0'\n"
        "    mov     byte [r9], dl\n"
        "    dec     r9\n"
        "    test    rax, rax\n"
        "    jnz     .putint_loop\n"
        "    test    r10, r10\n"
        "    jz      .putint_write\n"
        "    mov     byte [r9], '-'\n"
        "    dec     r9\n"
        ".putint_write:\n"
        "    inc     r9\n"
        "    lea     rdx, [rbp-20]\n"
        "    sub     rdx, r9\n"
        "    add     rdx, 2\n"
        "    mov     rax, 1\n"
        "    mov     rdi, 1\n"
        "    mov     rsi, r9\n"
        "    syscall\n"
        "    leave\n"
        "    ret\n"
        "\n"
        "; getchar() : lit un caractère depuis stdin, retourne dans rax\n"
        "getchar:\n"
        "    push    rbp\n"
        "    mov     rbp, rsp\n"
        "    sub     rsp, 16\n"
        "    mov     rax, 0\n"
        "    mov     rdi, 0\n"
        "    lea     rsi, [rbp-1]\n"
        "    mov     rdx, 1\n"
        "    syscall\n"
        "    test    rax, rax\n"
        "    jle     .getchar_eof\n"
        "    movzx   rax, byte [rbp-1]\n"
        "    leave\n"
        "    ret\n"
        ".getchar_eof:\n"
        "    mov     rax, -1\n"
        "    leave\n"
        "    ret\n"
        "\n"
        "; getint() : lit un entier décimal depuis stdin, retourne dans rax\n"
        "getint:\n"
        "    push    rbp\n"
        "    mov     rbp, rsp\n"
        "    sub     rsp, 16\n"
        "    xor     r8, r8\n"
        "    mov     r9, 1\n"
        "    mov     rax, 0\n"
        "    mov     rdi, 0\n"
        "    lea     rsi, [rbp-1]\n"
        "    mov     rdx, 1\n"
        "    syscall\n"
        "    movzx   rcx, byte [rbp-1]\n"
        "    cmp     rcx, '-'\n"
        "    je      .getint_minus\n"
        "    cmp     rcx, '+'\n"
        "    je      .getint_plus\n"
        "    cmp     rcx, '0'\n"
        "    jl      .getint_err\n"
        "    cmp     rcx, '9'\n"
        "    jg      .getint_err\n"
        "    sub     rcx, '0'\n"
        "    mov     r8, rcx\n"
        "    jmp     .getint_loop\n"
        ".getint_minus:\n"
        "    mov     r9, -1\n"
        ".getint_plus:\n"
        "    mov     rax, 0\n"
        "    mov     rdi, 0\n"
        "    lea     rsi, [rbp-1]\n"
        "    mov     rdx, 1\n"
        "    syscall\n"
        "    movzx   rcx, byte [rbp-1]\n"
        "    cmp     rcx, '0'\n"
        "    jl      .getint_err\n"
        "    cmp     rcx, '9'\n"
        "    jg      .getint_err\n"
        "    sub     rcx, '0'\n"
        "    mov     r8, rcx\n"
        ".getint_loop:\n"
        "    mov     rax, 0\n"
        "    mov     rdi, 0\n"
        "    lea     rsi, [rbp-1]\n"
        "    mov     rdx, 1\n"
        "    syscall\n"
        "    movzx   rcx, byte [rbp-1]\n"
        "    cmp     rcx, 10\n"
        "    je      .getint_done\n"
        "    cmp     rcx, '0'\n"
        "    jl      .getint_err\n"
        "    cmp     rcx, '9'\n"
        "    jg      .getint_err\n"
        "    sub     rcx, '0'\n"
        "    imul    r8, r8, 10\n"
        "    add     r8, rcx\n"
        "    jmp     .getint_loop\n"
        ".getint_done:\n"
        "    imul    r8, r9\n"
        "    mov     rax, r8\n"
        "    leave\n"
        "    ret\n"
        ".getint_err:\n"
        "    mov     rax, 60\n" 
        "    mov     rdi, 5\n"
        "    syscall\n"
        "\n"
    );
}

/* =========================================================
 *  Génération d'expressions → résultat dans rax
 * ========================================================= */
static void emit_expr(Node *expr, struct definition_info *func, FILE *fp);

/*
 * emit_load_var — charge la valeur d'une variable dans rax.
 *
 * Ordre de recherche : paramètres → locaux → globaux.
 * Variables locales/paramètres : accès via [rbp - offset].
 *   L'offset est stocké dans la table des symboles en comptant depuis 0,
 *   on ajoute 8 pour sauter le rbp sauvegardé sur la pile.
 * Variables globales : accès via [label] (section .bss).
 * Les char sont sign-étendus vers 64 bits (movsx/movsxd).
 */
static void emit_load_var(const char *name, struct definition_info *func,
                          FILE *fp) {
    if (func) {
        struct variable_info *p = func->liste_champs;
        while (p) {
            if (strcmp(p->identifiant, name) == 0) {
                if (p->type_nature == CHAR)
                    fprintf(fp, "    movsx   rax, byte [rbp - %ld]\n", (long)p->adresse + 8);
                else
                    fprintf(fp, "    movsxd  rax, dword [rbp - %ld]\n", (long)p->adresse + 8);
                return;
            }
            p = p->next;
        }
        struct variable_info *l = func->liste_locaux;
        while (l) {
            if (strcmp(l->identifiant, name) == 0) {
                if (l->type_nature == CHAR)
                    fprintf(fp, "    movsx   rax, byte [rbp - %ld]\n", (long)l->adresse + 8);
                else
                    fprintf(fp, "    movsxd  rax, dword [rbp - %ld]\n", (long)l->adresse + 8);
                return;
            }
            l = l->next;
        }
    }
    /* global: look up type in globalTable to choose byte/dword ops */
    {
        struct variable_info *gvar = find_variable(name, NULL, globalTable, size);
        if (gvar && gvar->type_nature == CHAR) {
            fprintf(fp, "    movzx   eax, byte [%s]\n", name);
            fprintf(fp, "    movsxd  rax, eax\n");
        } else {
            fprintf(fp, "    mov     eax, dword [%s]\n", name);
            fprintf(fp, "    movsxd  rax, eax\n");
        }
    }
}

/*
 * emit_store_var — stocke rax dans une variable (LValue).
 *
 * Même logique que emit_load_var pour la résolution.
 * Pour les int on écrit eax (32 bits, NASM étend à 64 en .bss).
 * Pour les char on écrit al (8 bits).
 */
static void emit_store_var(const char *name, struct definition_info *func,
                           FILE *fp) {
    /* rax contient la valeur à stocker */
    if (func) {
        struct variable_info *p = func->liste_champs;
        while (p) {
            if (strcmp(p->identifiant, name) == 0) {
                if (p->type_nature == CHAR)
                    fprintf(fp, "    mov     byte [rbp - %ld], al\n", (long)p->adresse + 8);
                else
                    fprintf(fp, "    mov     dword [rbp - %ld], eax\n", (long)p->adresse + 8);
                return;
            }
            p = p->next;
        }
        struct variable_info *l = func->liste_locaux;
        while (l) {
            if (strcmp(l->identifiant, name) == 0) {
                if (l->type_nature == CHAR)
                    fprintf(fp, "    mov     byte [rbp - %ld], al\n", (long)l->adresse + 8);
                else
                    fprintf(fp, "    mov     dword [rbp - %ld], eax\n", (long)l->adresse + 8);
                return;
            }
            l = l->next;
        }
    }
    /* global: write using byte for CHAR, dword for INT */
    {
        struct variable_info *gvar = find_variable(name, NULL, globalTable, size);
        if (gvar && gvar->type_nature == CHAR) {
            fprintf(fp, "    mov     byte [%s], al\n", name);
        } else {
            fprintf(fp, "    mov     dword [%s], eax\n", name);
        }
    }
}

/*
 * emit_expr — évalue une expression et place le résultat dans rax.
 *
 * Traite récursivement tous les types d'expression TPC :
 *   NODE_NUM       → constante entière littérale
 *   NODE_CHARACTER → constante caractère (converti en ASCII)
 *   NODE_IDENT     → lecture d'une variable (via emit_load_var)
 *   NODE_UNARY     → négation arithmétique (neg rax)
 *   NODE_NOT       → négation logique (0 → 1, non-0 → 0)
 *   NODE_ADDSUB    → addition ou soustraction
 *   NODE_DIVSTAR   → multiplication, division entière, modulo
 *   NODE_AND/OR    → opérateurs bit-à-bit (pas de court-circuit ici)
 *   NODE_EQ        → égalité / inégalité (résultat 0 ou 1)
 *   NODE_ORDER     → comparaisons <, >, <=, >= (résultat 0 ou 1)
 *   NODE_CALL_FUNCTION → appel de fonction (conventions AMD64)
 *   NODE_DOT       → accès à un champ de structure
 *
 * Stratégie pour les opérations binaires :
 *   eval(gauche) → push rax
 *   eval(droite) → mov rbx, rax → pop rax
 *   rax = gauche, rbx = droite → opération → résultat dans rax
 */
static void emit_expr(Node *expr, struct definition_info *func, FILE *fp) {
    if (!expr) { fprintf(fp, "    xor     rax, rax\n"); return; }

    switch (expr->label) {

    case NODE_NUM:
        fprintf(fp, "    mov     rax, %s\n", expr->text);
        break;

    case NODE_CHARACTER: {
        int val = 0;
        if (expr->text[1] == '\\') {
            switch (expr->text[2]) {
                case 'n':  val = 10; break;
                case 't':  val = 9;  break;
                case '0':  val = 0;  break;
                case '\\': val = '\\'; break;
                case '\'': val = '\''; break;
                default:   val = expr->text[2]; break;
            }
        } else {
            val = (unsigned char)expr->text[1];
        }
        fprintf(fp, "    mov     rax, %d\n", val);
        break;
    }

    case NODE_IDENT:
        emit_load_var(expr->text, func, fp);
        break;

    case NODE_UNARY:
        emit_expr(expr->firstChild, func, fp);
        fprintf(fp, "    neg     rax\n");
        break;

    case NODE_NOT:
        emit_expr(expr->firstChild, func, fp);
        fprintf(fp, "    test    rax, rax\n");
        fprintf(fp, "    setz    al\n");
        fprintf(fp, "    movzx   rax, al\n");
        break;

    case NODE_ADDSUB:
    case NODE_DIVSTAR:
    case NODE_AND:
    case NODE_OR:
    case NODE_EQ:
    case NODE_ORDER: {
        Node *left  = expr->firstChild;
        Node *right = left ? left->nextSibling : NULL;
        emit_expr(left, func, fp);
        fprintf(fp, "    push    rax\n");
        emit_expr(right, func, fp);
        fprintf(fp, "    mov     rbx, rax\n");
        fprintf(fp, "    pop     rax\n");

        if (expr->label == NODE_ADDSUB) {
            fprintf(fp, "    %s     rax, rbx\n", expr->text[0]=='+' ? "add" : "sub");
        } else if (expr->label == NODE_DIVSTAR) {
            if (expr->text[0] == '*') {
                fprintf(fp, "    imul    rax, rbx\n");
            } else if (expr->text[0] == '/') {
                fprintf(fp, "    cqo\n    idiv    rbx\n");
            } else {
                fprintf(fp, "    cqo\n    idiv    rbx\n    mov     rax, rdx\n");
            }
        } else if (expr->label == NODE_AND) {
            fprintf(fp, "    and     rax, rbx\n");
        } else if (expr->label == NODE_OR) {
            fprintf(fp, "    or      rax, rbx\n");
        } else if (expr->label == NODE_EQ) {
            fprintf(fp, "    cmp     rax, rbx\n");
            fprintf(fp, "    %s    al\n", (expr->text[0]=='=' ? "sete" : "setne"));
            fprintf(fp, "    movzx   rax, al\n");
        } else if (expr->label == NODE_ORDER) {
            fprintf(fp, "    cmp     rax, rbx\n");
            if      (strcmp(expr->text,"<" )==0) fprintf(fp,"    setl    al\n");
            else if (strcmp(expr->text,">" )==0) fprintf(fp,"    setg    al\n");
            else if (strcmp(expr->text,"<=")==0) fprintf(fp,"    setle   al\n");
            else if (strcmp(expr->text,">=")==0) fprintf(fp,"    setge   al\n");
            fprintf(fp, "    movzx   rax, al\n");
        }
        break;
    }

    case NODE_CALL_FUNCTION: {
        Node *fname_node = expr->firstChild;
        if (!fname_node) break;
        const char *fname = fname_node->text;
        const char *argregs[] = {"rdi","rsi","rdx","rcx","r8","r9"};
        Node *args[6];
        int nargs = 0;
        Node *arg = fname_node->nextSibling;
        if (arg && arg->label == NODE_Arguments)
            arg = arg->firstChild;
        while (arg && nargs < 6) { args[nargs++] = arg; arg = arg->nextSibling; }
        for (int i = 0; i < nargs; i++) {
            emit_expr(args[i], func, fp);
            fprintf(fp, "    push    rax\n");
        }
        for (int i = nargs-1; i >= 0; i--)
            fprintf(fp, "    pop     %s\n", argregs[i]);
        fprintf(fp, "    call    %s\n", fname);
        break;
    }

    case NODE_DOT: {
        Node *var_node   = expr->firstChild;
        Node *field_node = var_node ? var_node->nextSibling : NULL;
        if (!var_node || !field_node) break;
        struct variable_info *var = find_variable(var_node->text, func, globalTable, size);
        if (var && var->type_def) {
            struct variable_info *field = var->type_def->liste_champs;
            while (field) {
                if (strcmp(field->identifiant, field_node->text) == 0) {
                    if (field->type_nature == CHAR) {
                        if (var->container == NULL)
                            fprintf(fp, "    movzx   eax, byte [%s + %ld]\n", var_node->text, field->adresse);
                        else
                            fprintf(fp, "    movzx   eax, byte [rbp - %ld]\n", var->adresse + 8 - field->adresse);
                        fprintf(fp, "    movsxd  rax, eax\n");
                    } else {
                        if (var->container == NULL)
                            fprintf(fp, "    mov     eax, dword [%s + %ld]\n", var_node->text, field->adresse);
                        else
                            fprintf(fp, "    mov     eax, dword [rbp - %ld]\n", var->adresse + 8 - field->adresse);
                        fprintf(fp, "    movsxd  rax, eax\n");
                    }
                    break;
                }
                field = field->next;
            }
        }
        break;
    }

    case NODE_ListExp:
        if (expr->firstChild)
            emit_expr(expr->firstChild, func, fp);
        break;

    default:
        fprintf(fp, "    xor     rax, rax  ; expr label=%d non supportée\n", expr->label);
        break;
    }
}

/* =========================================================
 *  Génération des instructions
 * ========================================================= */
static void emit_instr_list(Node *instr, struct definition_info *func, FILE *fp);

/*
 * emit_instr — génère le code NASM pour une instruction TPC.
 *
 *   NODE_ASSIGN          → évalue rvalue dans rax, stocke dans lvalue
 *   NODE_IF (avec/sans else) → saut conditionnel sur test de rax
 *   NODE_WHILE           → boucle avec étiquettes while_start/while_end
 *   NODE_RETURN          → évalue l'expression, saute à l'épilogue
 *   NODE_CALL_FUNCTION   → appel de fonction (valeur de retour ignorée)
 *
 * Les étiquettes sont générées avec new_label() pour éviter les doublons
 * entre plusieurs if/while dans la même fonction.
 */
static void emit_instr(Node *node, struct definition_info *func, FILE *fp) {
    if (!node) return;

    switch (node->label) {

    case NODE_ASSIGN: {
        Node *lvalue = node->firstChild;
        Node *rvalue = lvalue ? lvalue->nextSibling : NULL;
        if (!lvalue || !rvalue) break;
        emit_expr(rvalue, func, fp);
        if (lvalue->label == NODE_IDENT) {
            emit_store_var(lvalue->text, func, fp);
        } else if (lvalue->label == NODE_DOT) {
            Node *var_node   = lvalue->firstChild;
            Node *field_node = var_node ? var_node->nextSibling : NULL;
            if (var_node && field_node) {
                struct variable_info *var = find_variable(var_node->text, func, globalTable, size);
                if (var && var->type_def) {
                    struct variable_info *field = var->type_def->liste_champs;
                    while (field) {
                        if (strcmp(field->identifiant, field_node->text) == 0) {
                            if (field->type_nature == CHAR) {
                                if (var->container == NULL)
                                    fprintf(fp, "    mov     byte [%s + %ld], al\n", var_node->text, field->adresse);
                                else
                                    fprintf(fp, "    mov     byte [rbp - %ld], al\n", var->adresse + 8 - field->adresse);
                            } else {
                                if (var->container == NULL)
                                    fprintf(fp, "    mov     dword [%s + %ld], eax\n", var_node->text, field->adresse);
                                else
                                    fprintf(fp, "    mov     dword [rbp - %ld], eax\n", var->adresse + 8 - field->adresse);
                            }
                            break;
                        }
                        field = field->next;
                    }
                }
            }
        }
        break;
    }

    case NODE_IF: {
        Node *cond      = node->firstChild;
        Node *then_body = cond ? cond->nextSibling : NULL;
        Node *else_body = then_body ? then_body->nextSibling : NULL;
        int lbl = new_label();
        emit_expr(cond, func, fp);
        fprintf(fp, "    test    rax, rax\n");
        if (else_body) {
            fprintf(fp, "    jz      .else_%d\n", lbl);
            emit_instr_list(then_body->firstChild, func, fp);
            fprintf(fp, "    jmp     .endif_%d\n", lbl);
            fprintf(fp, ".else_%d:\n", lbl);
            emit_instr_list(else_body->firstChild, func, fp);
            fprintf(fp, ".endif_%d:\n", lbl);
        } else {
            fprintf(fp, "    jz      .endif_%d\n", lbl);
            if (then_body) emit_instr_list(then_body->firstChild, func, fp);
            fprintf(fp, ".endif_%d:\n", lbl);
        }
        break;
    }

    case NODE_WHILE: {
        Node *cond = node->firstChild;
        Node *body = cond ? cond->nextSibling : NULL;
        int lbl = new_label();
        fprintf(fp, ".while_start_%d:\n", lbl);
        emit_expr(cond, func, fp);
        fprintf(fp, "    test    rax, rax\n");
        fprintf(fp, "    jz      .while_end_%d\n", lbl);
        if (body) emit_instr_list(body->firstChild, func, fp);
        fprintf(fp, "    jmp     .while_start_%d\n", lbl);
        fprintf(fp, ".while_end_%d:\n", lbl);
        break;
    }

    case NODE_RETURN: {
        Node *retval = node->firstChild;
        if (retval)
            emit_expr(retval, func, fp);
        else
            fprintf(fp, "    xor     rax, rax\n");
        fprintf(fp, "    jmp     .%s_epilogue\n",
                func ? func->identifiant : "main");
        break;
    }

    case NODE_CALL_FUNCTION:
        emit_expr(node, func, fp);
        break;

    case NODE_IDENT:
        if (node->firstChild && node->firstChild->label == NODE_Arguments)
            emit_expr(node, func, fp);
        break;

    default:
        emit_expr(node, func, fp);
        break;
    }
}

static void emit_instr_list(Node *instr, struct definition_info *func, FILE *fp) {
    while (instr) { emit_instr(instr, func, fp); instr = instr->nextSibling; }
}

/* =========================================================
 *  Génération d'une fonction complète
 * ========================================================= */
/*
 * emit_function — génère le code NASM complet d'une fonction TPC.
 *
 * Structure émise :
 *   label:              ; nom de la fonction
 *       push rbp        ; prologue standard AMD64
 *       mov  rbp, rsp
 *       sub  rsp, N     ; N = taille du bloc d'activation (alignée 16)
 *       ...corps...
 *   .fname_epilogue:    ; cible des instructions return
 *       leave           ; restaure rsp et rbp
 *       ret             ; (ou syscall exit pour main)
 *
 * Pour main : l'épilogue fait syscall exit(rax) directement au lieu
 * d'un ret, car _start ne peut pas retourner normalement au kernel.
 *
 * La taille du bloc d'activation (total_size dans definition_info)
 * est alignée sur 16 octets pour respecter les conventions AMD64.
 */
static void emit_function(Node *funcNode, FILE *fp) {
    if (!funcNode || funcNode->label != NODE_DeclFonct) return;
    Node *enTete = funcNode->firstChild;
    Node *corps  = enTete->nextSibling;
    Node *typeNode = enTete->firstChild;
    Node *nameNode = typeNode->nextSibling;
    if (typeNode->label == NODE_STRUCT) nameNode = nameNode->nextSibling;
    const char *fname = nameNode->text;

    struct definition_info *func_def = find_in_table_symbole(fname, globalTable, size);
    int stack_size = func_def ? func_def->total_size : 0;
    if (stack_size % 16 != 0) stack_size = (stack_size / 16 + 1) * 16;

    if (strcmp(fname, "main") == 0) 
        fprintf(fp, "\nmain:\n");
    else {
        fprintf(fp, "\n; ----- %s -----\n%s:\n", fname, fname);
        fprintf(fp, "    push    rbp\n");
        fprintf(fp, "    mov     rbp, rsp\n");
        if (stack_size > 0) fprintf(fp, "    sub     rsp, %d\n", stack_size);
    }

    Node *suite = corps ? corps->firstChild : NULL;
    if (suite && suite->label == NODE_DeclVars) suite = suite->nextSibling;
    if (suite) emit_instr_list(suite->firstChild, func_def, fp);

    fprintf(fp, ".%s_epilogue:\n", fname);
    if (strcmp(fname, "main") == 0) {
        fprintf(fp, "    mov     rdi, rax\n");
        fprintf(fp, "    mov     rax, 60\n");
        fprintf(fp, "    syscall\n");
    } else {
        fprintf(fp, "    leave\n");
        fprintf(fp, "    ret\n");
    }
}

/* =========================================================
 *  Point d'entrée public
 * ========================================================= */
void parcours_instruction(Node *root, struct table_symbole *gtable, FILE *fp) {
    if (!root || !gtable || !fp) return;

    fprintf(fp, "\nsection .text\n");
    fprintf(fp, "global main\n\n");

    emit_builtin_io(fp);

    Node *current = root->firstChild;
    while (current) {
        if (current->label == NODE_DeclFoncts) {
            Node *func_node = current->firstChild;
            while (func_node) {
                if (func_node->label == NODE_DeclFonct)
                    emit_function(func_node, fp);
                func_node = func_node->nextSibling;
            }
        }
        current = current->nextSibling;
    }
}
