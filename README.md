# 25HEC001_raytracing

Un moteur de raytracing développé en C++ avec une architecture modulaire.

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

- CMake >= 3.10
- Compilateur C++17 (GCC, Clang, ou MSVC)
- Git

### Compilation

```bash
# Cloner le repository
git clone https://github.com/Adam-Doria/25HEC001_raytracing.git
cd 25HEC001_raytracing

# Configurer avec CMake
cmake -B build

# Compiler
cmake --build build

# Exécuter
./build/rayborn
```

### Build rapide

```bash
# Tout en une ligne
cmake -B build && cmake --build build && ./build/rayborn
```

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

```bash
cmake --build build
```

### Nettoyer le build

```bash
rm -rf build
cmake -B build
cmake --build build
```

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

## 📝 Conventions de code

- **Headers** : Extension `.hpp` avec `#pragma once`
- **Sources** : Extension `.cpp`
- **Namespaces** : Un namespace par module (`maths`, `core`, `image`)
- **Standard** : C++17

## 🎯 Roadmap

- [x] Architecture modulaire
- [x] Configuration CMake
- [ ] Implémentation des vecteurs 3D
- [ ] Système de rayons
- [ ] Caméra basique
- [ ] Rendu de sphères
- [ ] Export d'images (PPM)
- [ ] Matériaux et éclairage
- [ ] Antialiasing
- [ ] Réflexions et réfractions

## 📄 License

Ce projet est développé dans le cadre d'un projet académique à HETIC.
