#include <iostream>
#include "sdk_tests.hpp"
#include "sdk.hpp"

using namespace Tests;

void Tests::memory_cell_test() {
    std::cout << "#### MEMORY CELL TEST ####" << std::endl;

    NodeData node_data = NodeData();

    Memory::MemoryCell memory_cell = Memory::MemoryCell(&node_data);

    node_data.create<FLIPFLOP>(NodePosition{ 1, 5, 0 })
        .connect_to(memory_cell.input_bit);

    memory_cell.output_bit.connect_to(
        node_data.create<LED>(NodePosition{ 2, 5, 0 })
    );

    node_data.create<BUTTON>(NodePosition{ 3, 5, 0 })
        .connect_to(memory_cell.update_bit);

    std::cout << node_data.compile() << std::endl << std::endl;
}

void Tests::register_test() {
    std::cout << "#### REGISTER TEST ####" << std::endl;

    NodeData node_data = NodeData();

    unsigned char register_size = 16;
    Memory::Register register1 = Memory::Register(&node_data, register_size);

    node_data.create<BUTTON>(NodePosition{ -5, 5, 0 })
        .connect_to(register1.update_bit);

    char count = 1;
    for (NodeRef bit : register1.input_bits) {
        node_data.create<FLIPFLOP>(NodePosition{ -5, 5, count })
            .connect_to(bit);

        count++;
    }

    count = 1;
    for (NodeRef bit : register1.output_bits) {
        bit.connect_to(
            node_data.create<LED>(NodePosition{ -5, 6, count })
        );

        count++;
    }

    std::cout << node_data.compile() << std::endl << std::endl;
}

void Tests::shift_register_test() {
    std::cout << "#### SHIFT REGISTER TEST ####" << std::endl;

    NodeData node_data = NodeData();

    Memory::ShiftRegister sregister = Memory::ShiftRegister(&node_data, 4);

    node_data.create<BUTTON>(NodePosition{ -5, 5, 0 })
        .connect_to(sregister.update_bit);
    node_data.create<FLIPFLOP>(NodePosition{ -5, 5, 1 })
        .connect_to(sregister.input_bit);

    char count = 1;
    for (NodeRef bit : sregister.output_bits) {
        bit.connect_to(
            node_data.create<LED>(NodePosition{ -5, 6, count })
        );

        count++;
    }

    std::cout << node_data.compile() << std::endl << std::endl;
}

void Tests::decoder_test() {
    std::cout << "#### DECODER TEST ####" << std::endl;

    NodeData node_data = NodeData();

    unsigned char data_bits = 3;
    Plexers::Decoder decoder = Plexers::Decoder(&node_data, data_bits);

    char count = 0;
    for (NodeRef bit : decoder.input_bits) {
        node_data.create<FLIPFLOP>(NodePosition{ -5, 5, count })
            .connect_to(bit);

        count++;
    }

    count = 0;
    for (NodeRef bit : decoder.output_bits) {
        bit.connect_to(
            node_data.create<LED>(NodePosition{ -5, 6, count })
        );

        count++;
    }

    std::cout << node_data.compile() << std::endl << std::endl;
}

void Tests::sram_test() {
    std::cout << "#### SRAM TEST ####" << std::endl;

    NodeData node_data = NodeData();

    Memory::SRAM sram = Memory::SRAM(&node_data, 1, 8);

    char count = 0;
    for (NodeRef bit : sram.addr_decoder.input_bits) {
        node_data.create<FLIPFLOP>(NodePosition{ -5, 5, count })
            .connect_to(bit);

        count++;
    }

    count = 0;
    for (NodeRef bit : sram.input_bits) {
        node_data.create<FLIPFLOP>(NodePosition{ -5, 4, count })
            .connect_to(bit);

        count++;
    }

    count = 0;
    for (NodeRef bit : sram.output_bits) {
        bit.connect_to(
            node_data.create<LED>(NodePosition{ -5, 3, count })
        );

        count++;
    }

    node_data.create<BUTTON>(NodePosition{ -5, 2, 0 })
        .connect_to(sram.write_bit);

    std::cout << node_data.compile() << std::endl << std::endl;
}