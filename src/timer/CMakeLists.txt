# Module Core
add_library(chrono STATIC)

target_sources(chrono
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/chrono_timer.cpp
)

target_include_directories(chrono
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

