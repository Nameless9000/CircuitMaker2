#pragma once
#include "data.h"

struct MemoryCell {
    NodeRef data_node;
    NodeRef value_node;
    NodeRef update_node;

    MemoryCell(NodeData* node_data) {
        NodeRef flipflop = node_data->create<FLIPFLOP>();
        NodeRef and_gate = node_data->create<AND>();
        NodeRef xor_gate = node_data->create<XOR>();

        xor_gate.connect_to(and_gate);
        and_gate.connect_to(flipflop);
        flipflop.connect_to(xor_gate);

        data_node = flipflop;
        value_node = xor_gate;
        update_node = and_gate;
    }
};

struct Register {
    std::vector<NodeRef> data_nodes;
    std::vector<NodeRef> value_nodes;
    NodeRef update_node;

    Register(NodeData* node_data, unsigned char size) {
        update_node = node_data->create<LED>();

        for (unsigned char i = 0; i < size; i++) {
            MemoryCell memory_cell = MemoryCell(node_data);

            update_node.connect_to(memory_cell.update_node);

            data_nodes.push_back(memory_cell.data_node);
            value_nodes.push_back(memory_cell.value_node);
        }
    }
};