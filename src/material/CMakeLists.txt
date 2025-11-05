# Module Material
add_library(material STATIC)

target_sources(material
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/material.cpp
)

target_include_directories(material
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(material
    PUBLIC
        core
        maths
)
