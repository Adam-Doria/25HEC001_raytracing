# Git Hooks

Ce dossier contient les Git hooks partagés pour le projet Rayborn.

## Installation

Depuis la racine du projet :

```bash
./install-hooks.sh
```

## Hooks disponibles

### `pre-commit`

**Objectif** : Formater automatiquement le code avec clang-format avant chaque commit.

**Fonctionnement** :

1. Détecte tous les fichiers C++ (`.cpp`, `.hpp`, `.h`) staged pour le commit
2. Les formate avec `clang-format` selon la configuration `.clang-format`
3. Re-stage les fichiers formatés
4. Continue le commit si tout se passe bien

**Prérequis** : `clang-format` doit être installé

```bash
sudo apt install clang-format  # Ubuntu/Debian
brew install clang-format      # macOS
```

---

### `commit-msg`

**Objectif** : Vérifier que les messages de commit respectent le format **Conventional Commits**.

**Format attendu** :

```
type(scope): description

# Exemples:
feat: ajouter le calcul de raytracing
feat(camera): implémenter la classe Camera
fix: corriger le calcul de vecteur normalisé
docs: mettre à jour le README
refactor(core): simplifier la logique de Ray
```

**Types autorisés** :

- `feat` : Nouvelle fonctionnalité
- `fix` : Correction de bug
- `docs` : Documentation
- `style` : Formatage (espaces, virgules, etc.)
- `refactor` : Refactoring du code
- `test` : Ajout/modification de tests
- `chore` : Maintenance, dépendances
- `perf` : Amélioration de performance
- `ci` : Intégration continue
- `build` : Système de build
- `revert` : Annulation d'un commit

**Exemples de messages rejetés** :

```bash
❌ "update code"           # Pas de type
❌ "add feature"           # Pas de type
❌ "feature: new thing"    # 'feature' n'est pas un type valide (use 'feat')
```

---

## Pourquoi utiliser des hooks ?

✅ **Cohérence** : Tout le code suit le même style  
✅ **Automatique** : Pas besoin d'y penser  
✅ **Gain de temps** : Évite les reviews pour le formatage  
✅ **Qualité** : Se concentrer sur la logique, pas le style

## Désactiver temporairement

Si vous devez commit sans formater (déconseillé) :

```bash
git commit --no-verify -m "message"
```
