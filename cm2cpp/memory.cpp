#include "memory.h"

using namespace Memory;

MemoryCell::MemoryCell() {}
MemoryCell::MemoryCell(NodeData* node_data) {
    NodeRef flipflop = node_data->create<FLIPFLOP>();
    NodeRef and_gate = node_data->create<AND>();
    NodeRef xor_gate = node_data->create<XOR>();

    xor_gate >> and_gate;
    and_gate >> flipflop;
    flipflop >> xor_gate;

    output_bit = flipflop;
    input_bit = xor_gate;
    update_bit = and_gate;
}

Register::Register(NodeData* node_data, unsigned char size) {
    update_bit = node_data->create<AND>();

    for (unsigned char i = 0; i < size; i++) {
        MemoryCell memory_cell = MemoryCell(node_data);

        update_bit >> memory_cell.update_bit;

        output_bits.push_back(memory_cell.output_bit);
        input_bits.push_back(memory_cell.input_bit);
    }
}

ShiftRegister::ShiftRegister(NodeData* node_data, unsigned char bits, bool should_loop) {
    update_bit = node_data->create<OR>();

    MemoryCell last_cell;
    for (unsigned char count = 0; count < bits; count++) {
        MemoryCell memory_cell = MemoryCell(node_data);

        update_bit >> memory_cell.update_bit;

        if (count == 0)
            input_bit = memory_cell.input_bit;
        else
            last_cell.output_bit >> memory_cell.input_bit;

        output_bits.push_back(memory_cell.output_bit);

        last_cell = memory_cell;
    }
}

SRAM::SRAM(NodeData* node_data, unsigned char select_bits, unsigned char register_size) {
    write_bit = node_data->create<LED>();

    addr_decoder = Plexers::Decoder(node_data, select_bits);

    for (unsigned char _ = 0; _ < register_size; _++) {
        input_bits.push_back(
            node_data->create<LED>()
        );

        output_bits.push_back(
            node_data->create<LED>()
        );
    }

    for (NodeRef select_bit : addr_decoder.output_bits) {
        Register data_register = Register(node_data, register_size);

        write_bit >> data_register.update_bit;
        select_bit >> data_register.update_bit;

        int count = 0;
        for (NodeRef bit : data_register.input_bits) {
            input_bits.at(count) >> bit;
            count++;
        }

        count = 0;
        for (NodeRef bit : data_register.output_bits) {
            NodeRef read_block = node_data->create<AND>();

            read_block
                << NodeVec{ bit, select_bit }
            >> output_bits.at(count);

            count++;
        }
    }
}