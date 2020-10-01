#include <cstring>
#include <iostream>

#include "train.h"

namespace Prog3C {
    carriage::carriage() {
        this->maximum_capacity = 0;
        this->occupied_seats_number = 0;
    }
    
    carriage::carriage(const int maximum_capacity, const int occupied_seats_number) {
        this->set_carriage(maximum_capacity, occupied_seats_number);
    }
    
    void train::cars_push_back(const carriage& main_carriage) {
        struct carriage *new_cars = new struct carriage[this->length + 1];
        
        memcpy(new_cars, cars, this->length * sizeof(struct carriage));        
        new_cars[this->length] = main_carriage;
        this->length++;
        delete[] cars;
        cars = new_cars;
    }
    
    carriage& carriage::set_carriage(const int maximum_capacity, const int occupied_seats_number) {
        if (maximum_capacity < 0 || occupied_seats_number < 0 || occupied_seats_number > maximum_capacity) {
           throw "Invalid carriage parameters!";
        }
        
        this->maximum_capacity = maximum_capacity;
        this->occupied_seats_number = occupied_seats_number;
        
        return *this;
    }
    
    void train::swap(train& another) {
        std::swap(this->cars, another.cars);
        std::swap(this->length, another.length);
    }
    
    train::train() {
        this->length = 1;
        this->cars = new struct carriage[this->length];
        this->cars[0] = { 0, 0 };
    }
    
    train::train(struct carriage *&cars, const int length) {
        this->set_carriages(cars, length);
    }
    
    train::train(const train& another) {
        this->length = another.length;
        if (!(this->length)) {
           this->cars = nullptr;
           return;
        }
        
        this->cars = new struct carriage[another.length];
        for (int i = 0; i < another.length; i++) {
            this->cars[i] = another.cars[i];
        }
    }
    
    train::train(train&& another) noexcept: train() {
        swap(another);
    }
    
    train::~train() {
        delete[] this->cars;
    }
    
    train& train::set_carriages(struct carriage *&cars, int length) {
        this->length = length;
        if (!(this->length)) {
           this->cars = nullptr;
           return *this;
        }
        
        this->cars = new struct carriage[this->length];
        this->cars[0] = { 0, 0 };
        for (int i = 1; i < this->length; i++) {
            this->cars[i] = cars[i];
        }
        
        return *this;
    }
    
    int train::get_length() const noexcept {
        return this->length;
    }
    
    struct carriage *train::get_carriages() const {
        return this->cars;
    }
    
    std::istream& operator >> (std::istream& in, train& main_train) {
        int maximum_capacity, occupied_seats_number;
        
        in >> maximum_capacity;
        in >> occupied_seats_number;
        if (occupied_seats_number > maximum_capacity) {
           throw "Invalid carriage parameters!";
        }
        
        main_train.cars_push_back({ maximum_capacity, occupied_seats_number });
        
        return in;
    }
    
    std::ostream& operator << (std::ostream& out, const train& main_train) {
        for (int i = 0; i < main_train.length; i++) {
            out << "Carriage #" << i << " occupancy: " << main_train.cars[i].occupied_seats_number << " passenger(s)\n";
        }
        
        return out;
    }
    
    train& train::operator = (const train& another) {
        if (this == &another) {
           return *this;
        }
        
        if (this->cars) {
           delete[] cars;
        }
        
        this->length = another.length;
        if (!(this->length)) {
           this->cars = nullptr;
           return *this;
        }
        
        this->cars = new struct carriage[another.length];
        for (int i = 0; i < another.length; i++) {
            this->cars[i] = another.cars[i];
        }
        
        return *this;
    }
    
    train& train::operator = (train&& another) noexcept {
        if (this != &another) {
           swap(another);
        }

        return *this;
    }
    
    train& train::operator () (const int carriage_index, const int seats_number) {
        if (seats_number < this->cars[carriage_index].maximum_capacity - this->cars[carriage_index].occupied_seats_number) {
           this->cars[carriage_index].occupied_seats_number += seats_number;
        }
        else {
           this->cars[carriage_index].occupied_seats_number = this->cars[carriage_index].maximum_capacity;
        }
        
        return *this;
    }
    
    const int& train::operator [] (const int carriage_index) const {
        return this->cars[carriage_index].occupied_seats_number;
    }
    
    train& train::operator += (const carriage& main_carriage) {
        cars_push_back(main_carriage);
        
        return *this;
    }
    
    train& train::operator ( ) (const int carriages_number, int *min_train) {
        for (int i = 0; i < carriages_number; i++) {
            for (int j = min_train[i] - i; j < this->length; j++) {
                cars[j] = cars[j + 1];
            }
            this->length--;
        }
        
        return *this;
    }
    
    int train::get_passengers_number() const {
        int passengers_number = 0;
        
        for (int i = 0; i < this->length; i++) {
            passengers_number += this->cars[i].occupied_seats_number;
        }
        
        return passengers_number;
    }
}