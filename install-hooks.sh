#!/bin/bash
# Script d'installation des Git hooks pour le projet Rayborn

echo "🔧 Installation des Git hooks..."

HOOKS_DIR=".git/hooks"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Vérifier qu'on est dans un repo Git
if [ ! -d ".git" ]; then
    echo "❌ Erreur: Ce script doit être exécuté à la racine du projet Git"
    exit 1
fi

# Copier le hook pre-commit
cp "${SCRIPT_DIR}/hooks/pre-commit" "${HOOKS_DIR}/pre-commit"
chmod +x "${HOOKS_DIR}/pre-commit"
echo "✅ Hook pre-commit installé"

# Copier le hook commit-msg
cp "${SCRIPT_DIR}/hooks/commit-msg" "${HOOKS_DIR}/commit-msg"
chmod +x "${HOOKS_DIR}/commit-msg"
echo "✅ Hook commit-msg installé"

echo ""
echo "📋 Les hooks vont automatiquement:"
echo "   - Formater le code avec clang-format avant chaque commit"
echo "   - Vérifier le format Conventional Commits des messages"
echo ""
echo "🎉 Installation terminée!"
