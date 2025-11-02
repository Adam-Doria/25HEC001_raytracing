
add_library(maths STATIC)

target_sources(maths
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/vector3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Color.cpp
)

target_include_directories(maths
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
