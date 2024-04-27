#include <iostream>
#include "sdk_tests.hpp"
#include "sdk.hpp"

using namespace Tests;

NodeData Tests::seven_segment_decimal_test() {
    std::cout << "#### SEVEN SEGMENT DECIMAL TEST ####" << std::endl;

    NodeData node_data = NodeData();

    Display::SevenSegmentDecimal display = Display::SevenSegmentDecimal(&node_data);

    for (char i = 0; i < 9; i++) {
        node_data.create<FLIPFLOP>(NodePosition{ i, 0, -1 }) >> display.bits[i];
    }

    display.a >> NodeVec{
        node_data.create<LED>(NodePosition{ 0, 12, 1 }, true),
        node_data.create<LED>(NodePosition{ 0, 12, 2 }, true),
        node_data.create<LED>(NodePosition{ 0, 12, 3 }, true)
    };
    display.b >> NodeVec{
        node_data.create<LED>(NodePosition{ 0, 9, 4 }, true),
        node_data.create<LED>(NodePosition{ 0, 10, 4 }, true),
        node_data.create<LED>(NodePosition{ 0, 11, 4 }, true)
    };
    display.c >> NodeVec{
        node_data.create<LED>(NodePosition{ 0, 5, 4 }, true),
        node_data.create<LED>(NodePosition{ 0, 6, 4 }, true),
        node_data.create<LED>(NodePosition{ 0, 7, 4 }, true)
    };
    display.d >> NodeVec{
        node_data.create<LED>(NodePosition{ 0, 4, 1 }, true),
        node_data.create<LED>(NodePosition{ 0, 4, 2 }, true),
        node_data.create<LED>(NodePosition{ 0, 4, 3 }, true)
    };
    display.e >> NodeVec{
        node_data.create<LED>(NodePosition{ 0, 5, 0 }, true),
        node_data.create<LED>(NodePosition{ 0, 6, 0 }, true),
        node_data.create<LED>(NodePosition{ 0, 7, 0 }, true),
    };
    display.f >> NodeVec{
        node_data.create<LED>(NodePosition{ 0, 9, 0 }, true),
        node_data.create<LED>(NodePosition{ 0, 10, 0 }, true),
        node_data.create<LED>(NodePosition{ 0, 11, 0 }, true)
    };
    display.g >> NodeVec{
        node_data.create<LED>(NodePosition{ 0, 8, 1 }, true),
        node_data.create<LED>(NodePosition{ 0, 8, 2 }, true),
        node_data.create<LED>(NodePosition{ 0, 8, 3 }, true)
    };

    return node_data;
}

NodeData Tests::memory_cell_test() {
    std::cout << "#### MEMORY CELL TEST ####" << std::endl;

    NodeData node_data = NodeData();

    Memory::MemoryCell memory_cell = Memory::MemoryCell(&node_data);

    memory_cell.input_bit
        << node_data.create<FLIPFLOP>(NodePosition{ 1, 5, 0 });

    memory_cell.output_bit
        >> node_data.create<LED>(NodePosition{ 2, 5, 0 }, true);

    memory_cell.update_bit
        << node_data.create<BUTTON>(NodePosition{ 3, 5, 0 });

    return node_data;
}

NodeData Tests::register_test() {
    std::cout << "#### REGISTER TEST ####" << std::endl;

    NodeData node_data = NodeData();

    unsigned char register_size = 16;
    Memory::Register register1 = Memory::Register(&node_data, register_size);

    register1.update_bit
        << node_data.create<BUTTON>(NodePosition{ -5, 5, 0 });

    char count = 1;
    for (NodeRef bit : register1.input_bits) {
        bit << node_data.create<FLIPFLOP>(NodePosition{ -5, 5, count });

        count++;
    }

    count = 1;
    for (NodeRef bit : register1.output_bits) {
        bit >> node_data.create<LED>(NodePosition{ -5, 6, count }, true);

        count++;
    }

    return node_data;
}

NodeData Tests::shift_register_test() {
    std::cout << "#### SHIFT REGISTER TEST ####" << std::endl;

    NodeData node_data = NodeData();

    Memory::ShiftRegister sregister = Memory::ShiftRegister(&node_data, 4);

    sregister.update_bit
        << node_data.create<BUTTON>(NodePosition{ -5, 5, 0 });

    sregister.input_bit
        << node_data.create<FLIPFLOP>(NodePosition{ -5, 5, 1 });

    char count = 1;
    for (NodeRef bit : sregister.output_bits) {
        bit >> node_data.create<LED>(NodePosition{ -5, 6, count }, true);

        count++;
    }

    return node_data;
}

NodeData Tests::decoder_test() {
    std::cout << "#### DECODER TEST ####" << std::endl;

    NodeData node_data = NodeData();

    unsigned char data_bits = 3;
    Plexers::Decoder decoder = Plexers::Decoder(&node_data, data_bits);

    char count = 0;
    for (NodeRef bit : decoder.input_bits) {
        bit << node_data.create<FLIPFLOP>(NodePosition{ -5, 5, count });

        count++;
    }

    count = 0;
    for (NodeRef bit : decoder.output_bits) {
        bit >> node_data.create<LED>(NodePosition{ -5, 6, count }, true);

        count++;
    }

    return node_data;
}

NodeData Tests::sram_test() {
    std::cout << "#### SRAM TEST ####" << std::endl;

    NodeData node_data = NodeData();

    Memory::SRAM sram = Memory::SRAM(&node_data, 1, 8);

    char count = 0;
    for (NodeRef bit : sram.addr_decoder.input_bits) {
        bit << node_data.create<FLIPFLOP>(NodePosition{ -5, 5, count });

        count++;
    }

    count = 0;
    for (NodeRef bit : sram.input_bits) {
        node_data.create<FLIPFLOP>(NodePosition{ -5, 4, count }) >> bit;

        count++;
    }

    count = 0;
    for (NodeRef bit : sram.output_bits) {
        bit >> node_data.create<LED>(NodePosition{ -5, 3, count }, true);

        count++;
    }

    sram.write_bit
        << node_data.create<BUTTON>(NodePosition{ -5, 2, 0 });

    return node_data;
}

NodeData Tests::full_adder_test()
{
    std::cout << "#### FULL ADDER TEST ####" << std::endl;

    NodeData node_data = NodeData();

    Arithmetic::FullAdder adder = Arithmetic::FullAdder(&node_data, 8);

    char count = 0;
    for (NodeRef bit : adder.input_bits1) {
        bit << node_data.create<FLIPFLOP>(NodePosition{ -5, 1, count });

        count++;
    }

    count = 0;
    for (NodeRef bit : adder.input_bits2) {
        bit << node_data.create<FLIPFLOP>(NodePosition{ -5, 2, count });

        count++;
    }

    count = 0;
    for (NodeRef bit : adder.output_bits) {
        bit >> node_data.create<LED>(NodePosition{ -5, 3, count }, true);

        count++;
    }

    adder.carry_bit
        >> node_data.create<LED>(NodePosition{ -5, 3, count }, true);

    return node_data;
}
