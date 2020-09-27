#include <iostream>

#include "train.h"

namespace Prog3A {
	carriage::carriage() {
		this->maximum_capacity = 0;
		this->occupied_places_number = 0;
	}
	
	carriage::carriage(int maximum_capacity, int occupied_places_number) {
		this->maximum_capacity = maximum_capacity;
		this->occupied_places_number = occupied_places_number;
	}
	
	carriage::set_maximum_capacity(int maximum_capacity) {
		if (maximum_capacity < 0) {
		   throw "Maximum capacity should be a non-negative number!";
		}
		this->maximum_capacity = maximum_capacity;
	}
	
	carriage::set_maximum_capacity(int maximum_capacity) {
		if (occupied_places_number < 0) {
		   throw "Number of occupied places should be non-negative!";
		}
		this->occupied_places_number = occupied_places_number;
	}
	
	train::train() {
		this->length = 1;
        this->cars = carriage carriages();
	}
	
	train::train(int length, struct carriage *cars) {
		this->set_train(length, cars);
	}
	
	train& train::set_train(int length, struct carriage *cars) {
		if (length < 0 || length > 100) {
		   throw length;
		}
		this->length = length;
		for (int i = 0; i < length; i++) {
		    this->cars[i] = cars[i];
		}
	}
	
	int train::get_length() const {
		return this->length;
	}
	
	std::ostream& operator>>(std::ostream& in, const train& Train) {
		for (int i = 0; i < Train.length; i++) {
			in >> Train.cars[i].maximum_capacity;
			in >> Train.cars[i].occupied_places_number;
	    }
	    return in;
    }
	
	std::ostream& operator<<(std::ostream& out, const train& Train) {
		for (int i = 0; i < Train.length; i++) {
			out << Train.cars[i] << " ";
	    }
	    return out;
    }
	
	train& train::operator()(int carriage_index, int places_number) {
		if (carriage_index < 1 || carriage_index > 99) {
		   throw carriage_index;
		}
		if (places_number < this->cars[carriage_index].maximum_capacity - this->cars[carriage_index].occupied_places_number) {
		   this->cars[carriage_index].occupied_places_number = this->cars[carriage_index].occupied_places_number + places_number;
		}
		else {
		   this->cars[carriage_index].occupied_places_number = this->cars[carriage_index].maximum_capacity;
		}
		return *this;
	}
	
	int& train::operator[](int carriage_index) const {
		return this->cars[carriage_index].occupied_places_number;
	}
	
	train& train::operator+=(int maximum_capacity, int occupied_places_number) {
		if (this->length == 100) {
		   throw length;
		}
		this->cars[length].maximum_capacity = maximum_capacity;
		this->cars[length].occupied_places_number = occupied_places_number;
		this->length++;
		return *this;
	}
	
	train& train::operator( )(int carriages_number, int *mini_train) {
		if (carriages_number < 0 || carriages_number > 100) {
		   throw carriages_number;
		}
		for (int i = 0; i < carriages_number; i++) {
		    for (int j = mini_train[i]; j < this->length; j++) {
                cars[j] = cars[j++];
		    }
			this->length--;
		}
		return *this;
	}