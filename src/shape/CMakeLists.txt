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
