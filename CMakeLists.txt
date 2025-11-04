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

# Ajout des sous-modules
add_subdirectory(src/core)
add_subdirectory(src/maths)
add_subdirectory(src/image)
add_subdirectory(src/lodepng)
add_subdirectory(src/tests)
add_subdirectory(src/timer)


# Exécutable principal
add_executable(rayborn src/main.cpp)

# Lier les modules à l'exécutable
target_link_libraries(rayborn
    PRIVATE
        core
        maths
        image
        lodepng
        chrono
        sphere

)

