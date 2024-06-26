#pragma once
#include "data.h"
#include "plexers.h"

namespace Memory {
    struct MemoryCell {
        NodeRef output_bit;
        NodeRef input_bit;
        NodeRef update_bit;

        MemoryCell();
        MemoryCell(NodeData* node_data);
    };

    struct Register {
        NodeVec output_bits;
        NodeVec input_bits;
        NodeRef update_bit;

        Register(NodeData* node_data, unsigned char size = 8);
    };

    struct ShiftRegister {
        NodeVec output_bits;
        NodeRef input_bit;
        NodeRef update_bit;

        ShiftRegister(NodeData* node_data, unsigned char bits = 8, bool should_loop = false);
    };

    struct SRAM {
        NodeVec output_bits;
        NodeVec input_bits;
        NodeRef write_bit;
        Plexers::Decoder addr_decoder;

        SRAM(NodeData* node_data, unsigned char select_bits = 2, unsigned char register_size = 8);
    };
}