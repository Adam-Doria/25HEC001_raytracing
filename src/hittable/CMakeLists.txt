# Module Core
add_library(hittable STATIC)

target_sources(hittable
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/hittable.cpp
)

target_include_directories(hittable
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

