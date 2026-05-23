# Rapport de Projet — Compilateur TPC → NASM

**Université Gustave Eiffel — Licence Informatique L3 — 2025-2026**

---

## 1. Présentation du projet

- Le but est d'écrire un compilateur en C pour le langage TPC
- Le langage cible est l'assembleur NASM en syntaxe ELF64 (conventions AMD64)
- Le compilateur détecte les erreurs lexicales, syntaxiques et sémantiques
- Il génère un fichier `.asm` exécutable sur Linux 64 bits

---

## 2. Organisation du projet

- `src/` : fichiers sources écrits par les humains
  - `tpcas.l` : analyseur lexical (Flex)
  - `tpcas.y` : analyseur syntaxique (Bison) + fonction `main` du compilateur
  - `tree.c` / `tree.h` : construction et affichage de l'AST
  - `compiler.c` / `compiler.h` : table des symboles + vérifications sémantiques
  - `instruction.c` / `instruction.h` : génération du code NASM
- `bin/` : binaire `tpcc`
- `obj/` : fichiers objets `.o`
- `rep/` : ce rapport
- `test/` : jeux de tests
  - `good/` : programmes TPC corrects (18 fichiers)
  - `syn-err/` : programmes avec erreurs syntaxiques (15 fichiers)
  - `sem-err/` : programmes avec erreurs sémantiques (10 fichiers)
  - `warn/` : programmes corrects avec avertissements (4 fichiers)

---

## 3. Choix de conception

### Analyse lexicale (Flex)
- Tous les tokens TPC sont reconnus : types, mots-clés, opérateurs, littéraux
- Les commentaires `//` et `/* */` sont ignorés
- Les caractères invalides produisent un message d'erreur avec numéro de ligne
- Les caractères littéraux mal formés (multi-char) sont détectés

### Analyse syntaxique (Bison)
- La grammaire couvre tout le langage TPC, y compris les structures
- Un seul conflit shift/reduce (`%expect 1`) pour le dangling else, résolu naturellement
- Chaque règle construit un nœud de l'AST avec `makeNode` et `addChild`

### Arbre abstrait (AST)
- Structure : chaque nœud a un label, un texte, un numéro de ligne, un premier enfant et un frère suivant
- Affichage textuel avec l'option `-t`
- Génération d'un fichier `.dot` pour Graphviz

### Table des symboles
- Table globale contenant variables globales, définitions de structures et fonctions
- Chaque fonction contient ses propres listes de paramètres et variables locales
- Les offsets mémoire sont calculés pour chaque variable
- Les 4 fonctions built-in (`getchar`, `putchar`, `getint`, `putint`) sont pré-insérées
- Détection des doublons (variables, paramètres, champs de struct)

### Vérifications sémantiques
- Variables et fonctions non déclarées → erreur
- Double déclaration → erreur
- Fonction `main` absente ou ne retournant pas `int` → erreur
- Champ de structure inexistant → erreur
- Fonction `void` utilisée comme expression → erreur
- Mauvais nombre d'arguments dans un appel de fonction → erreur
- `return` avec valeur dans une fonction `void` → erreur
- Affectation `int` vers `char` → avertissement
- `return int` dans une fonction `char` → avertissement

### Génération de code NASM
- Point d'entrée : `_start` appelle `main` puis fait `syscall exit`
- Chaque fonction a un prologue standard : `push rbp / mov rbp, rsp / sub rsp, N`
- Les paramètres sont passés par registres (rdi, rsi, rdx, rcx, r8, r9) et sauvegardés dans le bloc d'activation au prologue
- Les variables locales sont accédées via `[rbp - offset]`
- Les variables globales sont en section `.bss` et accédées par nom
- Les expressions sont évaluées via la pile (push/pop)
- Les structures de contrôle (`if/else`, `while`) utilisent des étiquettes uniques
- `putchar`, `putint`, `getchar`, `getint` sont écrits directement en NASM avec des syscalls Linux

### Interface utilisateur
- `./tpcc [OPTIONS] [FILE.tpc]` : compile un fichier TPC
- `./tpcc [OPTIONS] < FILE.tpc` : lit sur l'entrée standard
- Options : `-t` (arbre), `-s` (tables des symboles), `-h` (aide)
- Codes de retour : 0 (succès), 1 (erreur lexicale/syntaxique), 2 (erreur sémantique), 3 (autre erreur)
- Fichier cible : `FILE.asm` si fichier donné, `_anonymous.asm` sinon

---

## 4. Difficultés rencontrées

- **Prologue de `main`** : au début, `main` n'avait pas de prologue (`push rbp / mov rbp, rsp`), ce qui rendait les accès aux variables locales incorrects. Corrigé en unifiant le prologue pour toutes les fonctions.

- **Passage de paramètres** : les paramètres passés par registres AMD64 n'étaient pas sauvegardés dans le bloc d'activation. Les accès `[rbp - offset]` dans le corps de la fonction donnaient des valeurs aléatoires. Corrigé en ajoutant des `mov` au prologue pour copier chaque registre dans la pile.

- **Point d'entrée ELF** : le code utilisait `global main` au lieu de `global _start` avec un `_start:` qui appelle `main`. Sans `_start`, le binaire ne peut pas être lié avec `ld` seul.

- **Erreurs sur stdout** : certains messages d'erreur allaient sur `stdout` au lieu de `stderr`, ce qui polluait la sortie et faisait échouer les tests automatiques.

- **Conflit shift/reduce** : le dangling else (ambiguïté `if/else` imbriqués) produit un conflit shift/reduce que Bison résout naturellement par le shift (associer le `else` au `if` le plus proche).

- **Opérateurs logiques** : `&&` et `||` sont implémentés en bit-à-bit (`and`/`or`) sans court-circuit. C'est une simplification par rapport au C standard, mais le résultat est correct pour les cas booléens classiques.

---

## 5. Ce qui est implémenté

- Analyse lexicale complète
- Analyse syntaxique complète (avec extension structures)
- Construction de l'AST avec affichage et Graphviz
- Table des symboles complète (globales, fonctions, structures, locaux, paramètres)
- Vérifications sémantiques (variables, fonctions, types, arguments)
- Avertissements (int vers char, return type mismatch)
- Génération de code NASM fonctionnel :
  - Variables globales et locales
  - Expressions arithmétiques, logiques, relationnelles
  - Structures de contrôle (if/else, while)
  - Appels de fonctions (conventions AMD64, 6 registres)
  - Accès aux champs de structures
  - Fonctions built-in (putchar, putint, getchar, getint)
  - Fonctions récursives
- Script de test avec rapport et 4 scores globaux
- 4 jeux de tests : good (18), syn-err (15), sem-err (10), warn (4)

---

## 6. Ce qui n'est pas implémenté

- Court-circuit pour `&&` et `||` (évaluation paresseuse)
- Passage de plus de 6 arguments via la pile
- Fonctions retournant un `struct`
