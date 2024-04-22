#include <iostream>
#include <chrono>
#include "sdk_tests.h"

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    //Tests::memory_cell_test();

    //Tests::register_test();

    //Tests::decoder_test();

    Tests::sram_test();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Time taken: "
        << duration.count() << " microseconds" << std::endl;
}