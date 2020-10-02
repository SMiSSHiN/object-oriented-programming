#include <sstream>

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
    struct carriage cars[3];
    cars[0] = main_carriage_0;
    cars[1] = main_carriage_1;
    cars[2] = main_carriage_2;
    train main_train_1(cars, 3);
    ASSERT_NO_THROW(main_train_1);
    ASSERT_EQ(3, main_train_1.get_length());
    ASSERT_TRUE(0 == memcmp(cars, main_train_1.get_carriages(), sizeof(cars)));
    ASSERT_ANY_THROW(train main_train_2(cars, 0));
}

TEST(train_methods, basic_methods) {
    carriage main_carriage_0;
    carriage main_carriage_1(6, 4);
    carriage main_carriage_2(11, 5);
    struct carriage cars[3];
    cars[0] = main_carriage_0;
    cars[1] = main_carriage_1;
    cars[2] = main_carriage_2;
    train main_train_1;
    ASSERT_NO_THROW(main_train_1.set_length(3));
    ASSERT_EQ(3, main_train_1.get_length());
    ASSERT_NO_THROW(main_train_1.set_carriages(cars));
    ASSERT_TRUE(0 == memcmp(cars, main_train_1.get_carriages(), sizeof(cars)));
    train main_train_2;
    ASSERT_ANY_THROW(main_train_2.set_length(-2));
}

TEST(train_methods, output) {
    carriage main_carriage_0;
    carriage main_carriage_1(5, 2);
    struct carriage cars[2];
    cars[0] = main_carriage_0;
    cars[1] = main_carriage_1;
    train main_train(cars, 2);
    std::stringstream ss;
    ss << main_train;
    ASSERT_EQ("Carriage #0 occupancy: 0 passenger(s)\nCarriage #1 occupancy: 2 passenger(s)\n", ss.str());
}

TEST(train_methods, occupy_seats) {
    carriage main_carriage_0;
    carriage main_carriage_1(18, 7);
    struct carriage cars[2];
    cars[0] = main_carriage_0;
    cars[1] = main_carriage_1;
    train main_train(cars, 2);
    main_train(1, 5);
    ASSERT_EQ(12, main_train.get_carriages()[1].occupied_seats_number);
}

TEST(train_methods, carriage_occupancy_information) {
    carriage main_carriage_0;
    carriage main_carriage_1(22, 15);
    struct carriage cars[2];
    cars[0] = main_carriage_0;
    cars[1] = main_carriage_1;
    train main_train(cars, 2);
    ASSERT_EQ(15, main_train[1]);
}

TEST(train_methods, add_carriage) {
    carriage main_carriage_0;
    carriage main_carriage_1(9, 4);
    carriage main_carriage_2(27, 16);
    struct carriage cars[2];
    cars[0] = main_carriage_0;
    cars[1] = main_carriage_1;
    train main_train(cars, 2);
    main_train += main_carriage_2;
    ASSERT_EQ(3, main_train.get_length());
    ASSERT_EQ(27, main_train.get_carriages()[2].maximum_capacity);
    ASSERT_EQ(16, main_train.get_carriages()[2].occupied_seats_number);
}

TEST(train_methods, train_unhook) {
    carriage main_carriage_0;
    carriage main_carriage_1(32, 17);
    carriage main_carriage_2(23, 14);
    carriage main_carriage_3(45, 22);
    carriage main_carriage_4(19, 11);
    struct carriage cars[4];
    cars[0] = main_carriage_0;
    cars[1] = main_carriage_1;
    cars[2] = main_carriage_2;
    cars[3] = main_carriage_3;
    cars[4] = main_carriage_4;
    train main_train(cars, 5);
    int min_train[2] = { 2, 4 };
    main_train( 2, min_train );
    ASSERT_EQ(3, main_train.get_length());
    ASSERT_EQ(45, main_train.get_carriages()[2].maximum_capacity);
    ASSERT_EQ(22, main_train.get_carriages()[2].occupied_seats_number);
}

TEST(train_methods, passengers_number) {
    carriage main_carriage_0;
    carriage main_carriage_1(8, 3);
    carriage main_carriage_2(49, 36);
    struct carriage cars[3];
    cars[0] = main_carriage_0;
    cars[1] = main_carriage_1;
    cars[2] = main_carriage_2;
    train main_train(cars, 3);
    ASSERT_EQ(39, main_train.get_passengers_number());
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}