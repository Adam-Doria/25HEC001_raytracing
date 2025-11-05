# Tests pour le projet rayborn

# Exécutable de tests pour vector3
add_executable(vector3_tests vector3_tests.cpp)

# Lier Google Test et le module maths
target_link_libraries(vector3_tests
    PRIVATE
        GTest::gtest_main
        maths
)

# Découvrir automatiquement les tests
include(GoogleTest)
gtest_discover_tests(vector3_tests)

