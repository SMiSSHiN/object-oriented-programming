#include "dialog.h"

namespace Prog3 {
    static constexpr int options_number = 5;
    
    using opt_t = void(*)(DICE&);

    static const opt_t options[options_number] = {
        &average_of_average,
        &try_your_luck,
        &deleting_concurrences,
        &another_test_for_your_luck,
        &dice_output
    };

    void dialog(DICE& dice) {
        int choice = 0;
        
        std::cout << "-----------------------------------------------------------------------------------------------------" << std::endl;
        while (true) {
           menu();
           std::cout << "-----------------------------------------------------------------------------------------------------" << std::endl;
           choice = getNum<int>("Your choice: ");
           std::cout << "-----------------------------------------------------------------------------------------------------" << std::endl;
           if (!choice) {
              break;
           }
           else if (choice < 0 || choice > options_number) {
              std::cout << "Invalid option detected!" << std::endl; 
           }
           else {
              options[choice - 1](dice);
           }
           std::cout << "-----------------------------------------------------------------------------------------------------" << std::endl;
        }
    }
    
    void menu() {
        std::cout <<
            "0. Quit" << std::endl <<
            "1. Average of average" << std::endl <<
            "2. Try your luck" << std::endl <<
            "3. Delete all the concurrences" << std::endl <<
            "4. Another test for your luck" << std::endl <<
            "5. Check the dices out" << std::endl;
    }
    
    void dice_output(DICE& dice) {
        std::cout << dice;
    }
    
    void average_of_average(DICE& dice) {
        int experiments_number = getNum<int>("Number of experiments: ");
        double sum_of_average = 0;
        
        if (!dice.get_r_number() || !experiments_number) {
           std::cout << "Invalid parameters!" << std::endl;
           return;
        }
        
        for (int i = 0; i < experiments_number; i++) {
            dice.roll_dice();
            sum_of_average += dice.get_sum_of_dice() / dice.get_r_number();
        }
        
        std::cout << "Average dices sum value for all experiments: " << sum_of_average / experiments_number << std::endl;
    }

    void try_your_luck(DICE& dice) {
        int target_value = getNum<int>("Target value: ");
        int attempts_counter = 0;
        int current_sum_of_dice;
        
        do {
            current_sum_of_dice = dice.get_sum_of_dice();
            try {
                dice += rand() % 6 + 1;
                attempts_counter++;
            }
            catch (const std::length_error& error) {
                std::cout << "Not this time, mate:)" << std::endl;
                return;
            }
        } while (dice.get_sum_of_dice() != current_sum_of_dice + target_value);
        
        std::cout << attempts_counter << " attempt(s) spent to retrieve the needed value!" << std::endl;
    }
    
    void deleting_concurrences(DICE& dice) {
        int attempts_counter = 0;
        
        do {
            try {
                dice -= rand() % 6 + 1;
                attempts_counter++;
            }
            catch (const std::logic_error& error) {
                if (!dice.find_concurrence()) {
                   std::cout << attempts_counter << " attempt(s) spent to delete all the concurrences!" << std::endl;
                }
                else {
                   std::cout << "Not this time, mate:)" << std::endl;
                }
                return;
            }
        } while (dice.find_concurrence());
        
        std::cout << attempts_counter << " attempt(s) spent to delete all the concurrences!" << std::endl;
    }
    
    void another_test_for_your_luck(DICE& dice) {
        int choice; 
        try {
            choice = dice[rand() % 10 + 1];
            std::cout << "You have choicen the dice value: " << choice << std::endl;
        }
        catch (const std::invalid_argument& error) {
            std::cout << "Not this time, mate:)" << std::endl;
        }
    }
}