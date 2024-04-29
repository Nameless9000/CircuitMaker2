#include <iostream>
#include <chrono>
#include "sdk_tests.hpp"
#include "SDK/data.hpp"

int main() {
    for (auto test : {
        Tests::memory_cell_test,
        Tests::register_test,
        Tests::decoder_test,
        Tests::sram_test,
        Tests::shift_register_test,
        Tests::seven_segment_decimal_test,
        Tests::full_adder_test,
        Tests::text_generation_test
    }) {
        auto start = std::chrono::high_resolution_clock::now();

        NodeData node_data = test();
        std::string save_string = node_data.compile();

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::microseconds>(stop - start);
        std::cout
            << "Time taken: "
            << duration.count()
            << " microseconds"
            << std::endl << std::endl;

        std::cout << save_string << std::endl << std::endl;
    }
}