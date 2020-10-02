#include <iostream>

#include "train.h"

namespace Prog3A {
    carriage::carriage() {
        this->maximum_capacity = 0;
        this->occupied_seats_number = 0;
    }
    
    carriage::carriage(int maximum_capacity, int occupied_seats_number) {
        this->set_carriage(maximum_capacity, occupied_seats_number);
    }
    
    carriage& carriage::set_carriage(int maximum_capacity, int occupied_seats_number) {
        if (maximum_capacity < 0 || occupied_seats_number < 0 || occupied_seats_number > maximum_capacity) {
           throw "Invalid carriage parameters!";
        }
        
        this->maximum_capacity = maximum_capacity;
        this->occupied_seats_number = occupied_seats_number;
        
        return *this;
    }
    
    train::train() {
        this->cars[0] = { 0, 0 };
        this->length = 1;
    }
    
    train::train(struct carriage *cars, int length) {
        if (length < 1) {
           throw "Invalid length!";
        }
        
        this->set_length(length);
        this->set_carriages(cars);
    }
    
    train& train::set_length(int length) {
        if (length < 1) {
           throw "Invalid length!";
        }

        this->length = length;
        
        return *this;
    }
    
    train& train::set_carriages(struct carriage *cars) {
        this->cars[0] = { 0, 0 };
        for (int i = 1; i < this->length; i++) {
            this->cars[i] = cars[i];
        }
        
        return *this;
    }
    
    int train::get_length() {
        return this->length;
    }
    
    struct carriage *train::get_carriages() {
        return this->cars;
    }
    
    std::istream& operator >> (std::istream& in, train& main_train) {
        int maximum_capacity, occupied_seats_number;
        
        in >> maximum_capacity;
        in >> occupied_seats_number;
        if (occupied_seats_number > maximum_capacity) {
           throw "Invalid carriage parameters!";
        }
        
        main_train.cars[main_train.length].maximum_capacity = maximum_capacity;
        main_train.cars[main_train.length].occupied_seats_number = occupied_seats_number;
        main_train.length++;
        
        return in;
    }
    
    std::ostream& operator << (std::ostream& out, const train& main_train) {
        for (int i = 0; i < main_train.length; i++) {
            out << "Carriage #" << i << " occupancy: " << main_train.cars[i].occupied_seats_number << " passenger(s)\n";
        }
        
        return out;
    }
    
    train& train::operator () (int carriage_index, int seats_number) {
        if (seats_number < this->cars[carriage_index].maximum_capacity - this->cars[carriage_index].occupied_seats_number) {
           this->cars[carriage_index].occupied_seats_number += seats_number;
        }
        else {
           this->cars[carriage_index].occupied_seats_number = this->cars[carriage_index].maximum_capacity;
        }
        
        return *this;
    }
    
    int& train::operator [] (int carriage_index) {
        return this->cars[carriage_index].occupied_seats_number;
    }
    
    train& train::operator += (carriage& main_carriage) {
        this->cars[this->length] = main_carriage;
        this->length++;
        
        return *this;
    }
    
    train& train::operator ( ) (int carriages_number, int *min_train) {
        for (int i = 0; i < carriages_number; i++) {
            for (int j = min_train[i] - i; j < this->length; j++) {
                cars[j] = cars[j + 1];
            }
            this->length--;
        }
        
        return *this;
    }
    
    int train::get_passengers_number() {
        int passengers_number = 0;
        
        for (int i = 0; i < this->length; i++) {
            passengers_number += this->cars[i].occupied_seats_number;
        }
        
        return passengers_number;
    }
}