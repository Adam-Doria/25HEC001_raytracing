add_library(scene STATIC scene.cpp scene.hpp)

target_include_directories(scene
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Lien avec les dépendances
target_link_libraries(scene
    PUBLIC
        nlohmann_json::nlohmann_json   # <- nécessaire pour json.hpp
        core
        sphere
        triangle
        plane
        cube
        material
)
