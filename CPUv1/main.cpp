#include <iostream>
#include "sdk.h"

int main() {
    NodeData node_data = NodeData();

    unsigned char register_size = 64;
    Register register1 = Register(&node_data, register_size);

    node_data.create<BUTTON>(NodePosition{ -5, 10, 0 })
        .connect_to(register1.update_node);

    char count = 1;
    for (NodeRef value_node : register1.value_nodes) {
        node_data.create<FLIPFLOP>(NodePosition{ -5, 10, count })
            .connect_to(value_node);

        count++;
    }

    count = 1;
    for (NodeRef data_node : register1.data_nodes) {
        data_node.connect_to(
            node_data.create<LED>(NodePosition{ -5, 11, count })
        );

        count++;
    }

    std::cout << node_data.compile() << std::endl;
}