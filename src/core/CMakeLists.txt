# Module Core
add_library(core STATIC)

target_sources(core
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ray.cpp
)

target_include_directories(core
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src
)

