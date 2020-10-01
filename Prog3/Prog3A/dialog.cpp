#include "dialog.h"

#define options_number 7

namespace Prog3A {
    typedef void(*opt_t)(train&);

    static const opt_t options[options_number] = {
        &set_train,
        &get_train_occupancy_information,
        &occupy_seats,
        &get_carriage_occupancy_information,
        &add_carriage,
        &unhook_train,
        &get_passengers_number
    };

    void dialog(train &main_train) {
        int choice = 0;
        
        std::cout << "------------------------------------------------------------" << std::endl;
        while (true) {
           menu();
           std::cout << "------------------------------------------------------------" << std::endl;
           choice = getNum<int>("Your choice: ");
           std::cout << "------------------------------------------------------------" << std::endl;
           if (!choice) {
              break;
           }
           else if (choice < 0 || choice > options_number) {
              std::cout << "Invalid option detected!" << std::endl; 
           }
           else {
              options[choice - 1](main_train);
           }
           std::cout << "------------------------------------------------------------" << std::endl;
        }
    }
    
    void menu() {
        std::cout <<
            "0. Quit" << std::endl <<
            "1. Set train" << std::endl <<
            "2. Get train occupancy information" << std::endl <<
            "3. Occupy seat" << std::endl <<
            "4. Get carriage occupancy information" << std::endl <<
            "5. Add carriage to train" << std::endl <<
            "6. Train unhook" << std::endl <<
            "7. Get passengers number" << std::endl;
    }
    
    void set_train(train& main_train) {
        int carriages_number = getNum<int>("Number of carriages to specify: ");
        int start_length = main_train.get_length();
        
        if (carriages_number < 1 || carriages_number > 100) {
           std::cout << "Invalid carriages number!" << std::endl;
           return;
        }
        
        for (int i = 1; i <= carriages_number; i++) {
            std::cout << "Carriage #" << i + start_length - 1 << " parameters: ";
            std::cin >> main_train;
        }
    }
    
    void get_train_occupancy_information(train& main_train) {
        std::cout << main_train;
    }
    
    void occupy_seats(train& main_train) {
        int carriage_index = getNum<int>("Carriage index: ");
        
        if (carriage_index < 1 || carriage_index > main_train.get_length() - 1) {
           std::cout << "Invalid carriage index!" << std::endl;
           return;
        }
        
        int seats_number = getNum<int>("Number of seats to be occupied: ");
        
        if (seats_number < 0 || seats_number > main_train.get_carriages()[carriage_index].maximum_capacity) {
           std::cout << "Invalid seats number!" << std::endl;
           return;
        }
        
        main_train(carriage_index, seats_number);
    }
    
    void get_carriage_occupancy_information(train& main_train) {
        int carriage_index = getNum<int>("Carriage index: ");
        
        if (carriage_index < 1 || carriage_index > main_train.get_length() - 1) {
           std::cout << "Invalid carriage index!" << std::endl;
           return;
        }
        
        std::cout << "Number of passengers in the carriage: " << main_train[carriage_index] << std::endl;
    }
    
    void add_carriage(train& main_train) {
        if (main_train.get_length() == 100) {
           std::cout << "Unable to add carriage!" << std::endl;
           return;           
        }
        
        int carriage_maximum_capacity = getNum<int>("Carriage maximum capacity: ");
        int carriage_occupied_seats_number = getNum<int>("Carriage occupied seats number: ");
        
        if (carriage_maximum_capacity < carriage_occupied_seats_number) {
           std::cout << "Invalid carriage parameters!" << std::endl;
           return;
        }
        
        try {
            carriage main_carriage(carriage_maximum_capacity, carriage_occupied_seats_number);
            main_train += main_carriage;
        }
        catch (const char *error) {
            std::cerr << error << std::endl;
        }
    }
    
    void unhook_train(train& main_train) {
        int carriages_number = getNum<int>("Number of carriages to unhook: ");
        
        if (carriages_number < 0 || carriages_number > main_train.get_length() - 1) {
           std::cout << "Invalid carriages number!" << std::endl;
           return;
        }
        
        int min_train[carriages_number];
        struct carriage mini_cars[carriages_number + 1];
              
        std::cout << "Carriages indexes: ";
        for (int i = 0; i < carriages_number; i++) {
            do {
                min_train[i] = getNum<int>("");
            } while (min_train[i] <= 0);
        }
        
        for (int i = 0; i < carriages_number; i++) {
            mini_cars[i + 1] = { main_train.get_carriages()[min_train[i]].maximum_capacity, main_train.get_carriages()[min_train[i]].occupied_seats_number };
        }
        
        main_train( carriages_number, min_train );
        
        train mini_train(mini_cars, carriages_number + 1);
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << "Formed mini-train occupancy information: " << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;
        std::cout << mini_train;
    }
    
    void get_passengers_number(train& main_train) {
        std::cout << "Number of passengers in the train: " << main_train.get_passengers_number() << std::endl;
    }
}