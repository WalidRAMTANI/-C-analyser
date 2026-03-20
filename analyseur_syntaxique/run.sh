#!/bin/bash

# Script pour compiler et exécuter un fichier .tpc
# Usage: ./run.sh fichier.tpc

if [ $# -ne 1 ]; then
    echo "Usage: $0 fichier.tpc"
    exit 1
fi

INPUT_FILE=$1

# Générer le code assembleur
echo "Génération du code assembleur..."
./tpcas "$INPUT_FILE"

# Assembler
echo "Assemblage..."
nasm -f elf64 _anonymous.asm -o _anonymous.o

# Lier
echo "Liaison..."
ld _anonymous.o -o _anonymous -lc -dynamic-linker /lib64/ld-linux-x86-64.so.2

# Exécuter
echo "Exécution:"
./_anonymous