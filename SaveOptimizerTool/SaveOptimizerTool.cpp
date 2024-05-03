#include <iostream>
#include "sdk.h"

int main() {
    std::cout << "[Save Optimizer Tool]\n";
    
    std::cout << "Enter your save string: ";

    std::string save_string_input;
    std::cin >> save_string_input;

    std::cout << std::endl;

    NodeData node_data;

    SaveData::SaveString save_string = SaveData::SaveString(save_string_input);
    save_string.import_string(&node_data);

    std::cout << std::endl
              << node_data.compile()
              << std::endl;

    system("pause"); // bad but works
}