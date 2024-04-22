#pragma once
#include "data.h"

struct MemoryCell {
    NodeRef output_bit;
    NodeRef input_bit;
    NodeRef update_bit;

    MemoryCell(NodeData* node_data) {
        NodeRef flipflop = node_data->create<FLIPFLOP>();
        NodeRef and_gate = node_data->create<AND>();
        NodeRef xor_gate = node_data->create<XOR>();

        xor_gate.connect_to(and_gate);
        and_gate.connect_to(flipflop);
        flipflop.connect_to(xor_gate);

        output_bit = flipflop;
        input_bit = xor_gate;
        update_bit = and_gate;
    }
};

struct Register {
    std::vector<NodeRef> output_bits;
    std::vector<NodeRef> input_bits;
    NodeRef update_bit;

    Register(NodeData* node_data, unsigned char size = 8) {
        update_bit = node_data->create<LED>();

        for (unsigned char i = 0; i < size; i++) {
            MemoryCell memory_cell = MemoryCell(node_data);

            update_bit.connect_to(memory_cell.update_bit);

            output_bits.push_back(memory_cell.output_bit);
            input_bits.push_back(memory_cell.input_bit);
        }
    }
};

struct SRAM {
    SRAM(NodeData* node_data, unsigned char register_count = 8, unsigned char register_size = 8);
};