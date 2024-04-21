#include <iostream>
#include "sdk.h"

struct MemoryCell {
    NodeRef value_node;
    NodeRef update_node;

    MemoryCell(NodeData* node_data) {
        NodeRef flipflop = node_data->create_flipflop();
        NodeRef and_gate = node_data->create_and();
        NodeRef xor_gate = node_data->create_xor();

        xor_gate.connect_to(and_gate);
        and_gate.connect_to(flipflop);
        flipflop.connect_to(xor_gate);

        value_node = xor_gate;
        update_node = and_gate;
    }
};

int main() {
    NodeData node_data = NodeData();
    MemoryCell memory_cell = MemoryCell(&node_data);

    node_data.create_flipflop(NodePosition { 0, 10, 0 })
        .connect_to(memory_cell.value_node);

    node_data.create_button(NodePosition { 0, 10, 5 })
        .connect_to(memory_cell.update_node);

    std::cout << node_data.compile();
}