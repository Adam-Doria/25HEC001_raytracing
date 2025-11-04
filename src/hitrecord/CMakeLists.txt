# Module Core
add_library(hitrecord STATIC)

target_sources(hitrecord
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/hitrecord.cpp
)

target_include_directories(hitrecord
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(hitrecord
    PUBLIC
        maths
        core
)