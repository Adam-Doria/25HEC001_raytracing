
add_library(lodepng STATIC)

target_sources(lodepng
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lodepng.cpp
)

target_include_directories(lodepng
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
