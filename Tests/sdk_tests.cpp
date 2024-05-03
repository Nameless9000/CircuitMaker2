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
    SaveData::SaveString data = SaveData::SaveString("5,0,-8,0,-1,0+0;5,0,-7,0,-1,0+0;5,0,-6,0,-1,0+0;5,0,-5,0,-1,0+0;5,0,-4,0,-1,0+0;5,0,-3,0,-1,0+0;5,0,-2,0,-1,0+0;5,0,0,0,-1,0+0;5,0,-1,0,-1,0+0;5,0,1,0,-1,0+0;5,0,2,0,-1,0+0;5,0,3,0,-1,0+0;5,1,4,0,-1,2+0;5,0,5,0,-1,0+0;1,0,0,0,0,;5,0,6,0,-1,0+0;1,0,-8,0,0,;1,0,-7,0,0,;1,0,-6,0,0,;1,0,-5,0,0,;1,0,-4,0,0,;1,0,-3,0,0,;1,0,-2,0,0,;1,0,-1,0,0,;1,0,6,0,0,;1,0,5,0,0,;1,0,4,0,0,;1,0,3,0,0,;1,0,2,0,0,;1,0,1,0,0,;15,0,7,0,1,;2,0,-8,0,-2,;2,0,-7,0,-2,;2,0,-6,0,-2,;2,0,-4,0,-2,;2,0,-3,0,-2,;2,0,-2,0,-2,;2,0,-1,0,-2,;2,0,0,0,-2,;2,0,2,0,-2,;2,0,3,0,-2,;2,0,6,0,-2,;2,0,-5,0,-2,;2,0,5,0,-2,;2,1,4,0,-2,;2,0,1,0,-2,;16,0,7,0,-2,4;2,1,7,0,-1,;2,0,7,0,0,;3,0,4,0,1,;1,0,6,0,1,;5,1,2,0,1,2+0;0,0,1,0,1,;5,1,3,0,1,2+0;1,0,5,0,1,;0,1,0,0,1,;5,0,7,0,3,0+0?1,32;2,33;3,34;4,43;5,35;6,36;7,37;8,39;9,38;10,46;11,40;12,41;13,45;14,44;15,8;16,42;17,1;18,2;19,3;20,4;21,5;22,6;23,7;24,9;25,16;26,14;27,13;28,12;29,11;30,10;2,17;3,17;3,18;4,17;4,18;4,19;5,17;5,18;5,19;5,20;6,17;6,18;6,19;6,20;6,21;7,17;7,18;7,19;7,20;7,21;7,22;9,17;9,18;9,19;9,20;9,21;9,22;9,23;8,17;8,18;8,19;8,20;8,21;8,22;8,23;8,24;10,17;10,18;10,19;10,20;10,21;10,22;10,23;10,24;10,15;11,17;11,18;11,19;11,20;11,21;11,22;11,23;11,24;11,15;11,30;12,17;12,18;12,19;12,20;12,21;12,22;12,23;12,24;12,15;12,30;12,29;13,17;13,18;13,19;13,20;13,21;13,22;13,23;13,24;13,15;13,30;13,29;13,28;14,17;14,18;14,19;14,20;14,21;14,22;14,23;14,24;14,15;14,30;14,29;14,28;14,27;16,17;16,18;16,19;16,20;16,21;16,22;16,23;16,24;16,15;16,30;16,29;16,28;16,27;16,26;48,49;49,48;51,54;50,53;56,53;55,52;54,50;52,50;50,56;53,17;49,55;50,47;48,51;53,25;53,26;53,27;53,28;53,29;53,30;53,15;53,23;53,24;53,22;53,21;53,20;53,19;53,18;31,51;31,55;57,31??");

    data.import_string(node_data);
}
