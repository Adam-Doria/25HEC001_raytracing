# Module Core
add_library(sphere STATIC)

target_sources(sphere
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/sphere.cpp
)

target_include_directories(sphere
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(sphere
    PUBLIC
        core
        maths
)

# Module Triangle
add_library(triangle STATIC)

target_sources(triangle
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/triangle.cpp
)

target_include_directories(triangle
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(triangle
    PUBLIC
        core
        maths
)

# Module Plane
add_library(plane STATIC)

target_sources(plane
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/plane.cpp
)

target_include_directories(plane
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(plane
    PUBLIC
        core
        maths
)

# Module Cube
add_library(cube STATIC)

target_sources(cube
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/cube.cpp
)

target_include_directories(cube
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(cube
    PUBLIC
        core
        maths
        triangle
)
