#include "gtest/gtest.h"

#include "train.cpp"

using namespace Prog3A;

TEST(carriage_constructor, default_constructor) {
    ASSERT_NO_THROW(carriage main_carriage);
}

TEST(carriage_constructor, initial_constructor) {
    ASSERT_NO_THROW(carriage main_carriage_1(14, 8););
    ASSERT_ANY_THROW(carriage main_carriage_2(5, 9););
}

TEST(carriage_method, setter) {
    carriage main_carriage_1;
    ASSERT_NO_THROW(main_carriage_1.set_carriage(12, 5));
    carriage main_carriage_2;
    ASSERT_ANY_THROW(main_carriage_2.set_carriage(6, 13));
}

TEST(train_constructor, default_constructor) {
    train main_train;
    ASSERT_NO_THROW(main_train);
    ASSERT_EQ(1, main_train.get_length());
    ASSERT_EQ(0, main_train.get_carriages()[0].maximum_capacity);
    ASSERT_EQ(0, main_train.get_carriages()[0].occupied_seats_number);
}

TEST(train_constructor, initial_constructor) {
    carriage main_carriage_0;
    carriage main_carriage_1(7, 3);
    carriage main_carriage_2(12, 7);
    struct carriage cars[2];
    cars[0] = main_carriage_0;
    cars[1] = main_carriage_1;
    cars[2] = main_carriage_2;
    train main_train_1(cars, 3);
    ASSERT_NO_THROW(main_train_1);
    ASSERT_EQ(3, main_train_1.get_length());
    ASSERT_TRUE(0 == memcmp(cars, main_train_1.get_carriages(), sizeof(cars)));
    ASSERT_ANY_THROW(train main_train_2(cars, 0));
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}