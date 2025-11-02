cmake_minimum_required(VERSION 3.10.0)
project(rayborn VERSION 0.1.0 LANGUAGES C CXX)

# Standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ajout des sous-modules
add_subdirectory(src/core)
add_subdirectory(src/maths)
add_subdirectory(src/image)
add_subdirectory(src/lodepng)

# Exécutable principal
add_executable(rayborn src/main.cpp)

# Lier les modules à l'exécutable
target_link_libraries(rayborn
    PRIVATE
        core
        maths
        image
        lodepng
)

