cmake_minimum_required(VERSION 3.10.0)
project(rayborn VERSION 0.1.0 LANGUAGES C CXX)

# Standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Activation des tests
enable_testing()

# Télécharger et configurer Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# Pour Windows: empêcher gtest d'override nos flags de compilateur
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Télécharger et configurer nlohmann_json
FetchContent_Declare(
  nlohmann_json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(nlohmann_json)

# Ajout des sous-modules
add_subdirectory(src/core)
add_subdirectory(src/maths)
add_subdirectory(src/lib)
add_subdirectory(src/image)
add_subdirectory(src/lodepng)
add_subdirectory(src/tests)
add_subdirectory(src/shape)
add_subdirectory(src/material)
add_subdirectory(src/scene)


# Exécutable principal
add_executable(rayborn src/main.cpp)

# Lier les modules à l'exécutable
target_link_libraries(rayborn
    PRIVATE
        rtweekend
        core
        maths
        image
        lodepng
        chrono
        sphere
  triangle
  plane
  cube
  material
  scene
)
