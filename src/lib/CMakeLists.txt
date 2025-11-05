add_library(rtweekend INTERFACE)
add_library(chrono STATIC)

target_sources(chrono
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/chrono_timer.cpp
)

target_include_directories(chrono
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(rtweekend
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(rtweekend
    INTERFACE
        core
        maths
)
