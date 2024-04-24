#pragma once
#include "data.hpp"
#include "plexers.hpp"

namespace Memory {
    struct MemoryCell {
        NodeRef output_bit;
        NodeRef input_bit;
        NodeRef update_bit;

        MemoryCell();
        MemoryCell(NodeData* node_data);
    };

    struct Register {
        std::vector<NodeRef> output_bits;
        std::vector<NodeRef> input_bits;
        NodeRef update_bit;

        Register(NodeData* node_data, unsigned char size = 8);
    };

    struct ShiftRegister {
        std::vector<NodeRef> output_bits;
        NodeRef input_bit;
        NodeRef update_bit;

        ShiftRegister(NodeData* node_data, unsigned char bits = 8, bool should_loop = false);
    };

    struct SRAM {
        std::vector<NodeRef> output_bits;
        std::vector<NodeRef> input_bits;
        NodeRef write_bit;
        Plexers::Decoder addr_decoder;

        SRAM(NodeData* node_data, unsigned char select_bits = 2, unsigned char register_size = 8);
    };
}