#pragma once

#include <iosfwd>

namespace Prog3A {
    struct carriage {
        int maximum_capacity;
        int occupied_places_number;
        carriage();
        carriage(int maximum_capacity, int occupied_places_number);
		carriage& set_maximum_capacity(int maximum_capacity);
		carriage& set_occupied_places_number(int occupied_places_number);
    };
    class train {
    private:
        struct carriage cars[100];
        int length;
    public:
        train();
        train(int length, struct carriage *cars);
        train& set_train(int length, struct carriage *cars);
        int get_length() const;
        friend std::istream& operator>>(std::istream& in, const train& Train);
        friend std::ostream& operator<<(std::ostream& out, const train& Train);
        train& operator()(int carriage_index, int places_number);
        int& operator[](int carriage_index) const;
        train& operator+=(int maximum_capacity, int occupied_places_number);
        train& operator( )(int carriages_number, int *mini_train);
        int get_passengers_number() const;
    };
}