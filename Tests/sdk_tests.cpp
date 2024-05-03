#include <iostream>
#include "sdk_tests.h"

using namespace Tests;

void Tests::seven_segment_decimal_test(NodeData* node_data) {
    std::cout << "#### SEVEN SEGMENT DECIMAL TEST ####" << std::endl;

    Display::SevenSegmentDecimal display = Display::SevenSegmentDecimal(node_data);

    for (short i = 0; i < 9; i++) {
        node_data->create<FLIPFLOP>(NodePosition{ i, 0, -1 }) >> display.bits[i];
    }

    display.a >> NodeVec{
        node_data->create<LED>(NodePosition{ 0, 12, 1 }, true),
        node_data->create<LED>(NodePosition{ 0, 12, 2 }, true),
        node_data->create<LED>(NodePosition{ 0, 12, 3 }, true)
    };
    display.b >> NodeVec{
        node_data->create<LED>(NodePosition{ 0, 9, 4 }, true),
        node_data->create<LED>(NodePosition{ 0, 10, 4 }, true),
        node_data->create<LED>(NodePosition{ 0, 11, 4 }, true)
    };
    display.c >> NodeVec{
        node_data->create<LED>(NodePosition{ 0, 5, 4 }, true),
        node_data->create<LED>(NodePosition{ 0, 6, 4 }, true),
        node_data->create<LED>(NodePosition{ 0, 7, 4 }, true)
    };
    display.d >> NodeVec{
        node_data->create<LED>(NodePosition{ 0, 4, 1 }, true),
        node_data->create<LED>(NodePosition{ 0, 4, 2 }, true),
        node_data->create<LED>(NodePosition{ 0, 4, 3 }, true)
    };
    display.e >> NodeVec{
        node_data->create<LED>(NodePosition{ 0, 5, 0 }, true),
        node_data->create<LED>(NodePosition{ 0, 6, 0 }, true),
        node_data->create<LED>(NodePosition{ 0, 7, 0 }, true),
    };
    display.f >> NodeVec{
        node_data->create<LED>(NodePosition{ 0, 9, 0 }, true),
        node_data->create<LED>(NodePosition{ 0, 10, 0 }, true),
        node_data->create<LED>(NodePosition{ 0, 11, 0 }, true)
    };
    display.g >> NodeVec{
        node_data->create<LED>(NodePosition{ 0, 8, 1 }, true),
        node_data->create<LED>(NodePosition{ 0, 8, 2 }, true),
        node_data->create<LED>(NodePosition{ 0, 8, 3 }, true)
    };
}

void Tests::memory_cell_test(NodeData* node_data) {
    std::cout << "#### MEMORY CELL TEST ####" << std::endl;

    Memory::MemoryCell memory_cell = Memory::MemoryCell(node_data);

    memory_cell.input_bit
        << node_data->create<FLIPFLOP>(NodePosition{ 1, 5, 0 });

    memory_cell.output_bit
        >> node_data->create<LED>(NodePosition{ 2, 5, 0 }, true);

    memory_cell.update_bit
        << node_data->create<BUTTON>(NodePosition{ 3, 5, 0 });
}

void Tests::register_test(NodeData* node_data) {
    std::cout << "#### REGISTER TEST ####" << std::endl;

    unsigned char register_size = 4;
    Memory::Register register1 = Memory::Register(node_data, register_size);

    register1.update_bit
        << node_data->create<BUTTON>(NodePosition{ -5, 5, 0 });

    short count = 1;
    for (NodeRef bit : register1.input_bits) {
        bit << node_data->create<FLIPFLOP>(NodePosition{ -5, 5, count });

        count++;
    }

    count = 1;
    for (NodeRef bit : register1.output_bits) {
        bit >> node_data->create<LED>(NodePosition{ -5, 6, count }, true);

        count++;
    }
}

void Tests::shift_register_test(NodeData* node_data) {
    std::cout << "#### SHIFT REGISTER TEST ####" << std::endl;

    Memory::ShiftRegister sregister = Memory::ShiftRegister(node_data, 4);

    sregister.update_bit
        << node_data->create<BUTTON>(NodePosition{ -5, 5, 0 });

    sregister.input_bit
        << node_data->create<FLIPFLOP>(NodePosition{ -5, 5, 1 });

    short count = 1;
    for (NodeRef bit : sregister.output_bits) {
        bit >> node_data->create<LED>(NodePosition{ -5, 6, count }, true);

        count++;
    }
}

void Tests::decoder_test(NodeData* node_data) {
    std::cout << "#### DECODER TEST ####" << std::endl;

    unsigned char data_bits = 3;
    Plexers::Decoder decoder = Plexers::Decoder(node_data, data_bits);

    short count = 0;
    for (NodeRef bit : decoder.input_bits) {
        bit << node_data->create<FLIPFLOP>(NodePosition{ -5, 5, count });

        count++;
    }

    count = 0;
    for (NodeRef bit : decoder.output_bits) {
        bit >> node_data->create<LED>(NodePosition{ -5, 6, count }, true);

        count++;
    }
}

void Tests::sram_test(NodeData* node_data) {
    std::cout << "#### SRAM TEST ####" << std::endl;

    Memory::SRAM sram = Memory::SRAM(node_data, 1, 4);

    short count = 0;
    for (NodeRef bit : sram.addr_decoder.input_bits) {
        bit << node_data->create<FLIPFLOP>(NodePosition{ -5, 5, count });

        count++;
    }

    count = 0;
    for (NodeRef bit : sram.input_bits) {
        node_data->create<FLIPFLOP>(NodePosition{ -5, 4, count }) >> bit;

        count++;
    }

    count = 0;
    for (NodeRef bit : sram.output_bits) {
        bit >> node_data->create<LED>(NodePosition{ -5, 3, count }, true);

        count++;
    }

    sram.write_bit
        << node_data->create<BUTTON>(NodePosition{ -5, 2, 0 });
}

void Tests::full_adder_test(NodeData* node_data)
{
    std::cout << "#### FULL ADDER TEST ####" << std::endl;

    Arithmetic::FullAdder adder = Arithmetic::FullAdder(node_data, 4);

    short count = 0;
    for (NodeRef bit : adder.input_bits1) {
        bit << node_data->create<FLIPFLOP>(NodePosition{ -5, 1, count });

        count++;
    }

    count = 0;
    for (NodeRef bit : adder.input_bits2) {
        bit << node_data->create<FLIPFLOP>(NodePosition{ -5, 2, count });

        count++;
    }

    count = 0;
    for (NodeRef bit : adder.output_bits) {
        bit >> node_data->create<LED>(NodePosition{ -5, 3, count }, true);

        count++;
    }

    adder.carry_bit_out
        >> node_data->create<LED>(NodePosition{ -5, 3, count }, true);
    adder.carry_bit_in
        << node_data->create<FLIPFLOP>(NodePosition{ -5, 2, -1 }, true);
}

void Tests::text_generation_test(NodeData* node_data)
{
    std::cout << "#### TEXT GENERATION TEST ####" << std::endl;

    Fun::generate_text(node_data, "Written in C++!\n\nThis is a test AAAAAAAA AAAAAAAA.", true, 15);
}

void Tests::import_test(NodeData* node_data)
{
    std::cout << "#### SAVE IMPORT TEST ####" << std::endl;

    std::string save_string;

    std::cout << "Enter save string: \n";
    std::cin >> save_string;

    SaveData::SaveString save_data = SaveData::SaveString(save_string);

    save_data.import_string(node_data);
}
