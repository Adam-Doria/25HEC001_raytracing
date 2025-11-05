#include <gtest/gtest.h>

#include <cmath>

#include "vector3.hpp"

// Test des constructeurs et accesseurs
// Test des constructeurs et accesseurs
TEST(Vector3Test, ConstructorsAndAccessors) {
    vector3 v0;  // default
    EXPECT_NEAR(v0.x(), 0.0f, 1e-6f);
    EXPECT_NEAR(v0.y(), 0.0f, 1e-6f);
    EXPECT_NEAR(v0.z(), 0.0f, 1e-6f);

    vector3 v1(1.0f, 2.0f, 3.0f);
    EXPECT_NEAR(v1.x(), 1.0f, 1e-6f);
    EXPECT_NEAR(v1.y(), 2.0f, 1e-6f);
    EXPECT_NEAR(v1.z(), 3.0f, 1e-6f);

    EXPECT_NEAR(v1[0], 1.0f, 1e-6f);
    EXPECT_NEAR(v1[1], 2.0f, 1e-6f);
    EXPECT_NEAR(v1[2], 3.0f, 1e-6f);

    v1[0] = 4.0f;
    v1[1] = 5.0f;
    v1[2] = 6.0f;
    EXPECT_NEAR(v1.x(), 4.0f, 1e-6f);
    EXPECT_NEAR(v1.y(), 5.0f, 1e-6f);
    EXPECT_NEAR(v1.z(), 6.0f, 1e-6f);
}

// Test des opérations arithmétiques
TEST(Vector3Test, ArithmeticOps) {
    vector3 a(1, 2, 3);
    vector3 b(4, 5, 6);

    auto c_add = a + b;
    EXPECT_NEAR(c_add.x(), 5.0f, 1e-6f);
    EXPECT_NEAR(c_add.y(), 7.0f, 1e-6f);
    EXPECT_NEAR(c_add.z(), 9.0f, 1e-6f);

    auto c_sub = b - a;
    EXPECT_NEAR(c_sub.x(), 3.0f, 1e-6f);
    EXPECT_NEAR(c_sub.y(), 3.0f, 1e-6f);
    EXPECT_NEAR(c_sub.z(), 3.0f, 1e-6f);

    auto c_mul = a * b;
    EXPECT_NEAR(c_mul.x(), 4.0f, 1e-6f);
    EXPECT_NEAR(c_mul.y(), 10.0f, 1e-6f);
    EXPECT_NEAR(c_mul.z(), 18.0f, 1e-6f);

    auto c_smul1 = a * 2.0f;
    EXPECT_NEAR(c_smul1.x(), 2.0f, 1e-6f);
    EXPECT_NEAR(c_smul1.y(), 4.0f, 1e-6f);
    EXPECT_NEAR(c_smul1.z(), 6.0f, 1e-6f);

    auto c_smul2 = 3.0f * a;
    EXPECT_NEAR(c_smul2.x(), 3.0f, 1e-6f);
    EXPECT_NEAR(c_smul2.y(), 6.0f, 1e-6f);
    EXPECT_NEAR(c_smul2.z(), 9.0f, 1e-6f);

    auto c_div = b / 2.0f;
    EXPECT_NEAR(c_div.x(), 2.0f, 1e-6f);
    EXPECT_NEAR(c_div.y(), 2.5f, 1e-6f);
    EXPECT_NEAR(c_div.z(), 3.0f, 1e-6f);

    vector3 acc(1, 1, 1);
    acc += vector3(2, 3, 4);
    EXPECT_NEAR(acc.x(), 3.0f, 1e-6f);
    EXPECT_NEAR(acc.y(), 4.0f, 1e-6f);
    EXPECT_NEAR(acc.z(), 5.0f, 1e-6f);

    vector3 s(1, -2, 3);
    s *= -2.0f;
    EXPECT_NEAR(s.x(), -2.0f, 1e-6f);
    EXPECT_NEAR(s.y(), 4.0f, 1e-6f);
    EXPECT_NEAR(s.z(), -6.0f, 1e-6f);

    auto neg = -a;
    EXPECT_NEAR(neg.x(), -1.0f, 1e-6f);
    EXPECT_NEAR(neg.y(), -2.0f, 1e-6f);
    EXPECT_NEAR(neg.z(), -3.0f, 1e-6f);
}

// Test de longueur, produit scalaire, produit vectoriel et vecteur unitaire
TEST(Vector3Test, LengthDotCrossUnit) {
    vector3 v(3, 4, 12);
    EXPECT_NEAR(v.length_squared(), 3 * 3 + 4 * 4 + 12 * 12, 1e-6f);
    EXPECT_NEAR(v.length(), std::sqrt(9 + 16 + 144), 1e-6f);

    vector3 a(1, 2, 3);
    vector3 b(4, -5, 6);
    EXPECT_NEAR(dot(a, b), 1 * 4 + 2 * (-5) + 3 * 6, 1e-6f);

    auto c = cross(a, b);
    EXPECT_NEAR(c.x(), 2 * 6 - 3 * (-5), 1e-6f);  // 12 + 15 = 27
    EXPECT_NEAR(c.y(), 3 * 4 - 1 * 6, 1e-6f);     // 12 - 6 = 6, but note sign in implementation
    EXPECT_NEAR(c.z(), 1 * (-5) - 2 * 4, 1e-6f);  // -5 - 8 = -13

    auto u = unit_vector(vector3(0, 3, 4));
    EXPECT_NEAR(u.length(), 1.0f, 1e-5f);
    EXPECT_NEAR(u.x(), 0.0f, 1e-5f);
    EXPECT_NEAR(u.y(), 3.0f / 5.0f, 1e-5f);
    EXPECT_NEAR(u.z(), 4.0f / 5.0f, 1e-5f);
}
