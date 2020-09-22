#include <math.h>

#include "gtest/gtest.h"

#include "Cassini.cpp"

using namespace Prog2;

TEST(Cassini_Constructor, Default_Constructor) {
    Cassini cassini;
    ASSERT_EQ(0, cassini.Get_Distance());
    ASSERT_EQ(0, cassini.Get_Focal_Parameter());
}

TEST(Cassini_Constructor, Init_Constructor) {
    Cassini cassini(4, 3);
    ASSERT_EQ(4, cassini.Get_Distance());
    ASSERT_EQ(3, cassini.Get_Focal_Parameter());
}

TEST(Cassini_Constructor, Exception) {
    ASSERT_NO_THROW(Cassini cassini_1);
    ASSERT_NO_THROW(Cassini cassini_2(15, 10));
    ASSERT_ANY_THROW(Cassini cassini_3(-20, 48));
    ASSERT_ANY_THROW(Cassini cassini_4(10, -30));
}

TEST(Cassini_Methods, Setters) {
    Cassini cassini;
    ASSERT_ANY_THROW(cassini.Set_Distance(-4));
    ASSERT_ANY_THROW(cassini.Set_Focal_Parameter(-3));
    ASSERT_EQ(8, cassini.Set_Distance(8).Get_Distance());
    ASSERT_EQ(6, cassini.Set_Focal_Parameter(6).Get_Focal_Parameter());
}

TEST(Cassini_Methods, Distance_Focal_Parameter) {
    Cassini cassini(3, 5);
    ASSERT_EQ(3, cassini.Get_Distance());
    ASSERT_EQ(5, cassini.Get_Focal_Parameter());
}

TEST(Cassini_Methods, Shape_Type) {
    Cassini cassini(23, 34);
    ASSERT_EQ("two separate ovals", cassini.Get_Shape_Type());
}

TEST(Cassini_Methods, Curvature_Radius) {
    Cassini cassini(8, 6);
    double r = fabs(pow(6, 2) * cos(M_PI / 2) + sqrt(pow(6, 4) * pow(cos(M_PI / 2), 2) + pow(8, 4) - pow(6, 4)));
    ASSERT_EQ((pow(8, 2) * r / (pow(r, 2) + cos(M_PI / 2) * pow(6, 2))), cassini.Get_Curvature_Radius(45));
}

TEST(Cassini_Methods, Inflection_Points_Coordinates) {
    Cassini cassini(5, 4);
    ASSERT_EQ((pow(((pow(5, 4) - pow(4, 4)) / 3), 0.25)), cassini.Get_Inflection_Points_Polar_Radius());
    ASSERT_EQ((acos((-1) * sqrt(((pow(5, 4) / pow(4, 4)) - 1) / 3))) * 180 / (2 * M_PI), cassini.Get_Inflection_Points_Polar_Angle());
}

TEST(Cassini_Methods, Equation_NULL) {
    Cassini cassini;
    ASSERT_EQ("(x ^ 2 + y ^ 2) ^ 2 = 0", cassini.Get_Equation());
}

TEST(Cassini_Methods, Equation_Not_NULL) {
    Cassini cassini(2, 3);
    ASSERT_EQ("(x ^ 2 + y ^ 2) ^ 2 - 18 * (x ^ 2 - y ^ 2) = -65", cassini.Get_Equation());
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}