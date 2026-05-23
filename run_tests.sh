#!/bin/bash
# Script de déploiement des tests — Compilateur TPC
# Produit un rapport unique avec 4 scores globaux.
#
# Usage : ./run_tests.sh [chemin_vers_tpcc]
#         Par défaut : ./bin/tpcc

TPCC="${1:-./bin/tpcc}"

if [ ! -x "$TPCC" ]; then
    echo "ERREUR : $TPCC n'est pas exécutable. Compilez d'abord avec 'make'."
    exit 1
fi

# Couleurs
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
NC='\033[0m'

echo "========================================================"
echo "  RAPPORT DE TESTS — Compilateur TPC"
echo "  Binaire : $TPCC"
echo "  Date    : $(date)"
echo "========================================================"
echo ""

total_pass=0
total_fail=0
total_tests=0

# --- Fonction utilitaire ---
run_test_suite() {
    local suite_name="$1"
    local test_dir="$2"
    local expected_code="$3"

    local pass=0
    local fail=0
    local count=0

    echo "--- $suite_name (code attendu = $expected_code) ---"

    if [ ! -d "$test_dir" ]; then
        echo -e "  ${RED}ERREUR : Répertoire $test_dir introuvable${NC}"
        echo ""
        return
    fi

    for f in "$test_dir"/*.tpc; do
        [ -f "$f" ] || continue
        count=$((count + 1))
        $TPCC "$f" > /dev/null 2>&1
        actual=$?
        basename=$(basename "$f")
        if [ "$actual" -eq "$expected_code" ]; then
            echo -e "  ${GREEN}✅ PASS${NC}  $basename  (code=$actual)"
            pass=$((pass + 1))
        else
            echo -e "  ${RED}❌ FAIL${NC}  $basename  (attendu=$expected_code, obtenu=$actual)"
            fail=$((fail + 1))
        fi
    done

    if [ "$count" -eq 0 ]; then
        echo "  (aucun fichier .tpc trouvé)"
    else
        echo ""
        echo -e "  Score : ${GREEN}$pass${NC}/$count"
    fi
    echo ""

    total_pass=$((total_pass + pass))
    total_fail=$((total_fail + fail))
    total_tests=$((total_tests + count))
}

# --- Exécuter les 4 jeux de tests ---
run_test_suite "1. Programmes corrects (good)"         "test/good"     0
run_test_suite "2. Erreurs syntaxiques (syn-err)"      "test/syn-err"  1
run_test_suite "3. Erreurs sémantiques (sem-err)"      "test/sem-err"  2
run_test_suite "4. Programmes avec warnings (warn)"    "test/warn"     0

# --- Test stdin ---
echo "--- 5. Test lecture stdin ---"
echo "int main(void) { return 0; }" | $TPCC > /dev/null 2>&1
stdin_code=$?
if [ "$stdin_code" -eq 0 ]; then
    echo -e "  ${GREEN}✅ PASS${NC}  stdin (code=$stdin_code)"
    total_pass=$((total_pass + 1))
else
    echo -e "  ${RED}❌ FAIL${NC}  stdin (attendu=0, obtenu=$stdin_code)"
    total_fail=$((total_fail + 1))
fi
total_tests=$((total_tests + 1))

# --- Vérifier que _anonymous.asm est créé sur stdin ---
if [ -f "_anonymous.asm" ]; then
    echo -e "  ${GREEN}✅ PASS${NC}  _anonymous.asm créé"
    rm -f _anonymous.asm
    total_pass=$((total_pass + 1))
else
    echo -e "  ${RED}❌ FAIL${NC}  _anonymous.asm non créé"
    total_fail=$((total_fail + 1))
fi
total_tests=$((total_tests + 1))
echo ""

# --- Résumé final ---
echo "========================================================"
echo "  RÉSUMÉ FINAL"
echo "========================================================"
echo -e "  Tests réussis  : ${GREEN}$total_pass${NC} / $total_tests"
echo -e "  Tests échoués  : ${RED}$total_fail${NC} / $total_tests"
percent=0
if [ "$total_tests" -gt 0 ]; then
    percent=$((total_pass * 100 / total_tests))
fi
echo -e "  Score global   : ${YELLOW}${percent}%${NC}"
echo "========================================================"

# Nettoyage des fichiers .asm générés dans les répertoires de test
find test/ -name "*.asm" -delete 2>/dev/null

exit $total_fail
