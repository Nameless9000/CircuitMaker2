#pragma once
#include "util.h"
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

struct AdvancedRegister {
    std::vector<NodeRef> output_bits;
    std::vector<NodeRef> input_bits;
    NodeRef write_block;

    AdvancedRegister(NodeData* node_data, unsigned char size = 8) {
        write_block = node_data->create<AND>();

        for (unsigned char i = 0; i < size; i++) {
            NodeRef flipflop = node_data->create<FLIPFLOP>();
            NodeRef and_gate = node_data->create<AND>();
            NodeRef xor_gate = node_data->create<XOR>();

            xor_gate.connect_to(and_gate);
            and_gate.connect_to(flipflop);
            flipflop.connect_to(xor_gate);

            write_block.connect_to(and_gate);

            output_bits.push_back(flipflop);
            input_bits.push_back(xor_gate);
        }
    }
};

struct SRAM {
    std::vector<NodeRef> output_bits;
    std::vector<NodeRef> input_bits;
    NodeRef write_bit;
    Decoder addr_decoder;

    SRAM(NodeData* node_data, unsigned char select_bits = 2, unsigned char register_size = 8) {
        write_bit = node_data->create<LED>();

        addr_decoder = Decoder(node_data, select_bits);

        for (unsigned char _ = 0; _ < register_size; _++) {
            input_bits.push_back(
                node_data->create<LED>()
            );

            output_bits.push_back(
                node_data->create<LED>()
            );
        }

        for (NodeRef select_bit : addr_decoder.output_bits) {
            AdvancedRegister aregister = AdvancedRegister(node_data, register_size);

            write_bit.connect_to(aregister.write_block);
            select_bit.connect_to(aregister.write_block);

            int count = 0;
            for (NodeRef bit : aregister.input_bits) {
                input_bits.at(count).connect_to(bit);
                count++;
            }

            count = 0;
            for (NodeRef bit : aregister.output_bits) {
                NodeRef read_block = node_data->create<AND>();
                
                bit.connect_to(read_block);
                select_bit.connect_to(read_block);

                read_block.connect_to(output_bits.at(count));
                count++;
            }
        }
    }
};