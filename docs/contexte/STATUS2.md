# 📊 État du Projet – Compilateur TPC → NASM
**Session 2 — après corrections interface + génération NASM**
**Dépôt :** https://github.com/WalidRAMTANI/-C-analyser
**Date limite :** 24 mai 2026 à 18h

---

## ✅ Ce qui fonctionne (vérifié sur machine réelle)

### Compilation
```
make clean && make   →  0 warning, 0 erreur
```
Le `make` va jusqu'à assembler `_anonymous.asm` avec nasm et produire un binaire `_anonymous` exécutable.

### Interface utilisateur
| Commande | Résultat | Attendu |
|---|---|---|
| `./tpcc` (stdin) | lit stdin, erreur si invalide | ✅ |
| `./tpcc -h` | affiche l'aide | ✅ |
| `./tpcc -s FILE.tpc` | affiche la table des symboles | ✅ |
| `./tpcc -t FILE.tpc` | affiche l'AST + génère `.dot` | ✅ |
| `./tpcc FILE.tpc` | génère `FILE.asm` | ✅ |
| stdin invalide → code 1 | `echo "a" \| ./tpcc` → `2: syntax error`, exit 1 | ✅ |
| erreur sémantique → code 2 | variable non déclarée | ✅ |
| succès → code 0 | programme valide | ✅ |

### Table des symboles (`-s`)
Affichée correctement avec :
- variables globales + offsets
- fonctions : type retour, paramètres, taille stack
- structs : champs + offsets
- built-ins pré-insérés : `getchar`, `putchar`, `getint`, `putint`

### Génération de code NASM
Le fichier `.asm` produit par `tp5.tpc` s'assemble avec nasm et s'exécute. Structure correcte :

```nasm
section .bss
    x resd 1        ; variables globales
    ...

section .text
global _start

; built-in I/O (syscalls Linux)
putchar: ...
putint:  ...
getchar: ...
getint:  ...

; fonctions utilisateur
main:
    push    rbp
    mov     rbp, rsp
    sub     rsp, N       ; bloc d'activation
    ...
.main_epilogue:
    mov     rdi, rax
    mov     rax, 60      ; syscall exit
    syscall

_start:
    call    main
    mov     rdi, rax
    mov     rax, 60
    syscall
```

**Instructions générées :**
- Affectations (variables globales ET locales) ✅
- `if` / `if-else` avec étiquettes ✅
- `while` avec étiquettes ✅
- `return` avec saut à l'épilogue ✅
- Expressions : constantes, variables, `+`,`-`,`*`,`/`,`%`, `&&`,`||`,`!`, `==`,`!=`,`<`,`>`,`<=`,`>=` ✅
- Accès champs struct (`.`) ✅
- Appels de fonctions (conventions AMD64 : rdi, rsi, rdx...) ✅
- `putchar`, `putint`, `getchar`, `getint` en NASM pur (syscalls) ✅

---

## ⚠️ Ce qui reste à faire

### 1. Structure de répertoires — NON CONFORME
Le sujet exige :
```
ProjetCompilationL3_NOM1_NOM2/
├── makefile          ← à la racine
├── src/              ← sources humains
├── bin/tpcc          ← binaire
├── obj/              ← fichiers intermédiaires .o
├── rep/              ← rapport
└── test/
    ├── good/         ← présent dans analyseur_syntaxique/test/
    ├── syn-err/      ← présent dans analyseur_syntaxique/test/
    ├── sem-err/      ← ABSENT
    └── warn/         ← ABSENT
```

**Actuellement :** tout est dans `analyseur_syntaxique/`, les `.o` et le binaire sont à la racine du dossier, pas dans `obj/` et `bin/`.

**À faire :**
- Créer la structure `ProjetCompilationL3_NOM1_NOM2/`
- Déplacer les sources dans `src/`
- Modifier le `makefile` pour compiler vers `bin/tpcc` et mettre les `.o` dans `obj/`
- Créer `test/sem-err/` avec au moins 5 fichiers `.tpc`
- Créer `test/warn/` avec au moins 3 fichiers `.tpc`

### 2. Jeux de tests manquants

#### `test/sem-err/` — à créer
Exemples de fichiers à écrire :
```
01_undeclared_var.tpc       → x = 5; (x non déclaré)
02_undeclared_func.tpc      → f(); (f non déclarée)
03_double_declaration.tpc   → int x; int x; (double déclaration globale)
04_wrong_struct_field.tpc   → p.z sur struct sans champ z
05_void_in_expr.tpc         → int x; x = putchar('a'); (void utilisé comme valeur)
```

#### `test/warn/` — à créer
```
01_int_to_char.tpc          → char c; c = 42; (int → char warning)
02_int_to_char_param.tpc    → appel fonction char avec int
03_return_int_in_char.tpc   → fonction char { return 65; }
```

### 3. Script de test — à vérifier/compléter
Le fichier `run.sh` existe dans `analyseur_syntaxique/` mais son contenu n'a pas été vérifié. Il doit :
- Lancer tous les tests des 4 dossiers
- Vérifier les codes de retour (0 pour `good/`, 1 pour `syn-err/`, 2 pour `sem-err/`, 0 pour `warn/`)
- Produire un rapport unique avec 4 scores globaux

### 4. Rapport — ABSENT
Le dossier `rep/` n'existe pas. Le rapport doit couvrir :
- Choix de conception (table des symboles, génération de code)
- Difficultés rencontrées
- Ce qui est implémenté / non implémenté

### 5. Bugs connus à corriger

#### Génération de code
- **Variables locales `char`** : `emit_store_var` écrit `al` mais `emit_load_var` fait `movsx` — vérifier la cohérence sur un programme réel avec des `char` locaux
- **Appels de fonctions avec >6 arguments** : non géré (peu probable en TPC mais à documenter)
- **Fonctions non-`main` retournant un `int`** : le `leave` est dans l'épilogue mais `main` fait `syscall` — vérifier que les autres fonctions font bien `leave / ret` et pas `syscall`

#### Analyse sémantique
- `printf`/`fprintf` dans `compiler.c` mélangent stdout et stderr pour les erreurs — certaines erreurs vont sur stdout (`printf("Error: ...")`) au lieu de stderr
- Les messages d'erreur doivent tous donner le numéro de ligne (certains ne le font pas encore)

#### Lexeur
- Les caractères invalides sont silencieusement ignorés (règle `.` → `{ }` dans `tpcas.l`) — le sujet dit qu'une erreur lexicale doit donner lieu à un message avec numéro de ligne

### 6. Fonctionnalités avancées (bonus)
- Fonctions récursives : le code actuel devrait les supporter (pas de limitation), à tester
- Paramètres de fonctions : passés via registres AMD64 mais jamais lus depuis `[rbp + offset]` dans la fonction appelée — **à implémenter** (actuellement les paramètres sont dans la table mais l'accès depuis le corps de la fonction utilise `[rbp - offset]` comme les locaux, ce qui est incorrect pour les paramètres passés par registres)

---

## 🔢 Score estimé (barème du sujet)

| Critère | Points | État actuel |
|---|---|---|
| **Évaluation automatique** | 8 pts | |
| — Analyse lexicale/syntaxique | ~3 pts | ✅ Bon |
| — Détection erreurs sémantiques | ~3 pts | ⚠️ Partiel (stdout vs stderr, pas de numéro de ligne partout) |
| — Codes de retour 0/1/2 | ~2 pts | ✅ Bon |
| **Production de code assembleur** | 3 pts | ✅ Fonctionnel (s'assemble et s'exécute) |
| **AST + Tables des symboles** | 3 pts | ✅ Bon |
| **Messages d'avertissement/erreur** | 2 pts | ⚠️ Partiel |
| **Organisation + Rapport + Tests** | 4 pts | ❌ Structure non conforme, sem-err/warn absents, rapport absent |
| **TOTAL estimé** | **20 pts** | **~13-15/20** |

---

## 🚨 Priorités pour la session suivante

1. **Corriger les `printf` → `fprintf(stderr,...)` dans `compiler.c`** — erreurs sur stdout = pénalité automatique
2. **Corriger l'accès aux paramètres de fonctions** — les paramètres sont passés par registres AMD64, il faut les sauvegarder dans le bloc d'activation au prologue
3. **Créer `test/sem-err/` et `test/warn/`** — points gratuits
4. **Créer la structure de répertoires conforme** + `makefile` à la racine
5. **Écrire le script `run.sh`** complet avec les 4 scores
6. **Corriger les erreurs lexicales silencieuses** dans `tpcas.l`
7. **Écrire le rapport** dans `rep/`
