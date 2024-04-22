#pragma once
#include "data.h"

struct MemoryCell {
    NodeRef output_node;
    NodeRef input_node;
    NodeRef update_node;

    MemoryCell(NodeData* node_data) {
        NodeRef flipflop = node_data->create<FLIPFLOP>();
        NodeRef and_gate = node_data->create<AND>();
        NodeRef xor_gate = node_data->create<XOR>();

        xor_gate.connect_to(and_gate);
        and_gate.connect_to(flipflop);
        flipflop.connect_to(xor_gate);

        output_node = flipflop;
        input_node = xor_gate;
        update_node = and_gate;
    }
};

struct Register {
    std::vector<NodeRef> output_nodes;
    std::vector<NodeRef> input_nodes;
    NodeRef update_node;

    Register(NodeData* node_data, unsigned char size) {
        update_node = node_data->create<LED>();

        for (unsigned char i = 0; i < size; i++) {
            MemoryCell memory_cell = MemoryCell(node_data);

            update_node.connect_to(memory_cell.update_node);

            output_nodes.push_back(memory_cell.output_node);
            input_nodes.push_back(memory_cell.input_node);
        }
    }
};