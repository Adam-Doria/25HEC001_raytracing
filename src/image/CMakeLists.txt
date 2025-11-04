add_library(image STATIC)

target_sources(image
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/image.cpp
)

target_include_directories(image
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(image
    PUBLIC
        maths
        lodepng
)

