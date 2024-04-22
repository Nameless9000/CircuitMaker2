#include <iostream>
#include "sdk_tests.h"

int main() {
    Tests::memory_cell_test();

    Tests::register_test();

    Tests::decoder_test();
}