## 🧪 Tests

Le projet utilise **Google Test** pour les tests unitaires. Les tests sont automatiquement téléchargés et configurés via CMake.

### Lancer les tests

#### Option 1 : 

```bash
# Depuis le répertoire de build
cd out/build/windows-debug  # ou linux-debug / macos-debug
ctest --output-on-failure
```

#### Option 2 : 

```bash
# Depuis le répertoire de build
."D:\M2\ray tracer\projet\25HEC001_raytracing\out\build\windows-debug\src\tests\vector3_tests.exe"
```


### Tests actuels

- **Vector3Test** : Tests pour la classe `vector3`
  - Constructeurs et accesseurs
  - Opérations arithmétiques (+, -, *, /)
  - Longueur, produit scalaire, produit vectoriel
