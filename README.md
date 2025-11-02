# 25HEC001_raytracing

Projet de développement d'un moteur de raytracing en c++

## 👥 Contributors

- Adam Drici
- Kader Bakayoko
- Elyes Ouramdane

## 📋 Description

Ce projet implémente un moteur de raytracing from scratch en C++, permettant de générer des images photoréalistes par simulation des rayons lumineux.

## 🏗️ Architecture

Le projet est organisé en modules indépendants :

```
25HEC001_raytracing/
├── src/
│   ├── main.cpp           # Point d'entrée du programme
│   ├── core/              # Module core - Logique principale du raytracing
│   │   ├── ray.hpp
│   │   ├── ray.cpp
│   │   └── CMakeLists.txt
│   ├── maths/             # Module maths - Vecteurs et opérations mathématiques
│   │   ├── vector3.hpp
│   │   ├── vector3.cpp
│   │   └── CMakeLists.txt
│   └── image/             # Module image - Gestion des images et pixels
│       ├── image.hpp
│       ├── image.cpp
│       └── CMakeLists.txt
├── CMakeLists.txt         # Configuration CMake principale
└── CMakePresets.json      # Presets de configuration
```

### Modules

- **`maths/`** : Gestion des vecteurs 3D, matrices et opérations mathématiques
- **`core/`** : Logique du raytracing (rayons, caméra, scène)
- **`image/`** : Génération et export d'images

## 🚀 Installation

### Prérequis

#### Sur votre machine locale

- CMake >= 3.10
- Compilateur C++17 (GCC, Clang, ou MSVC)
- Git
- **clang-format**
- **Doxygen** 

**Installation des outils optionnels :**

```bash
# Ubuntu/Debian
sudo apt install clang-format doxygen graphviz

# macOS
brew install clang-format doxygen graphviz

# Windows (avec chocolatey)
choco install llvm doxygen.install graphviz
```

#### Avec Docker (alternative)

- Docker

### 📥 Cloner le projet

```bash
git clone https://github.com/Adam-Doria/25HEC001_raytracing.git
cd 25HEC001_raytracing
```

---

## 💻 Option 1 : Développement local avec CMake Presets

Cette approche utilise les **CMake Presets** configurés pour votre plateforme (Linux, macOS, Windows).

### Lister les presets disponibles

**Presets disponibles :**

- `linux-debug` / `linux-release` (Linux) => Adam
- `macos-debug` / `macos-release` (macOS) => Kader
- `windows-debug` / `windows-release` (Windows) => Elyes

### Build avec presets

#### Mode Debug (développement)

```bash
# Configuration avec preset
cmake --preset linux-debug  # OU macos-debug OU windows-debug

# Compilation
cmake --build --preset linux-debug # OU macos-debug OU windows-debug

# Exécution
./out/build/linux-debug/rayborn # OU /macos-debug/ OU /windows-debug/
```

#### Mode Release (production)

```bash
# Configuration avec preset
cmake --preset linux-release  # ou macos-release / windows-release

# Compilation
cmake --build --preset linux-release # ou macos-release / windows-release

# Exécution
./out/build/linux-release/rayborn # ou macos-release / windows-release
```

### Build et execution en 1 ligne

```bash
# Debug
cmake --preset linux-debug && cmake --build --preset linux-debug && ./out/build/linux-debug/rayborn

# Release
cmake --preset linux-release && cmake --build --preset linux-release && ./out/build/linux-release/rayborn
```

---

## 🐳 Option 2 : Développement avec Docker

Si vous ne voulez pas installer les dépendances localement, ou si vous rencontrez une erreur avec les presets, utilisez Docker. Cette option est **indépendante des presets CMake** et utilise une configuration manuelle.
On utilise le docker qu'en dev, pour des questions de performance.

### Étapes

```bash
# 1. Build de l'image Docker
docker build -t rayborn-dev .

# 2. Lancer le container à la racine du projet avec un volume monté correspondant à votre code
docker run -it --rm -v $(pwd):/app rayborn-dev

# 3. Dans le container Docker, compiler manuellement
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/rayborn
```

**Notes importantes :**

- ⚠️ Les **presets CMake ne fonctionnent pas dans Docker** (chemins de compilateurs différents)
- ✅ Vos modifications de code sont **synchronisées en temps réel**
- ✅ Vous éditez sur votre machine, vous compilez dans le container

---

## 🛠️ Développement

### Ajouter des fichiers à un module

1. Créer vos fichiers `.hpp` et `.cpp` dans le module concerné
2. Mettre à jour le `CMakeLists.txt` du module :

```cmake
target_sources(maths
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/vector3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/matrix.cpp  # Nouveau fichier
)
```

3. Recompiler :

**Avec CMake Presets :**

```bash
cmake --build --preset linux-debug  # ou votre preset
```

**Avec Docker :**

```bash
cmake --build build
```

### Nettoyer le build

**Avec CMake Presets :**

```bash
# Supprimer le dossier de build
rm -rf out/

# Reconstruire from scratch
cmake --preset linux-debug
cmake --build --preset linux-debug
```

**Avec Docker :**

```bash
# Dans le container
rm -rf build
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

### Différence Debug vs Release

La différence va se jouer sur l'optomisation, les perf et le temps de compilation.
La debug sera moins performante avec un temps de compilation court, c'est interessant pour tester le projet
La realease inversement sera pour tester notre perf et donc idéale pour la démo.

**En résumé :**

- 🛠️ **Debug** : Pendant le développement pour faciliter le débogage
- 🎯 **Release** : Pour la démo avec Kévin et les tests de performance

---

## 🎨 Formatage et Documentation

### Clang-Format (formatage automatique du code)

Le projet utilise `clang-format` pour maintenir un style de code cohérent.

**Formater un fichier :**

```bash
clang-format -i src/main.cpp
```

**Formater tous les fichiers du projet :**

```bash
find src/ -name "*.cpp" -o -name "*.hpp" | xargs clang-format -i
```

**Vérifier le formatage sans modifier :**

```bash
clang-format --dry-run --Werror src/main.cpp
```

### Doxygen (génération de documentation)

Le projet utilise `Doxygen` pour générer la documentation automatique du code.

**Générer la documentation :**

```bash
doxygen Doxyfile
```

La documentation HTML sera générée dans `docs/html/`. Ouvrez `docs/html/index.html` dans votre navigateur.

**Exemple de commentaire Doxygen :**

```cpp
/**
 * @brief Classe représentant un vecteur 3D
 *
 * Cette classe gère les opérations mathématiques sur des vecteurs 3D
 * utilisés pour le raytracing.
 */
class Vector3 {
public:
    /**
     * @brief Constructeur par défaut
     * @param x Composante X
     * @param y Composante Y
     * @param z Composante Z
     */
    Vector3(double x, double y, double z);
};
```

---

## 📦 Structure des modules CMake

Chaque module est une bibliothèque statique indépendante :

- **Headers publics** : Accessibles par les autres modules
- **Sources privées** : Implémentation interne du module
- **Dépendances** : Gérées via `target_link_libraries`

Exemple de dépendance :

```cmake
# Si image dépend de core et maths
target_link_libraries(image PUBLIC core maths)
```

## 📄 License

Ce projet est développé dans le cadre d'un projet académique à HETIC.
