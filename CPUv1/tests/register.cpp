#include <iostream>
#include "../sdk.h"

static int run_test() {
    NodeData node_data = NodeData();

    unsigned char register_size = 16;
    Register register1 = Register(&node_data, register_size);

    node_data.create<BUTTON>(NodePosition{ -5, 10, 0 })
        .connect_to(register1.update_node);

    char count = 1;
    for (NodeRef input_node : register1.input_nodes) {
        node_data.create<FLIPFLOP>(NodePosition{ -5, 10, count })
            .connect_to(input_node);

        count++;
    }

    count = 1;
    for (NodeRef output_node : register1.output_nodes) {
        output_node.connect_to(
            node_data.create<LED>(NodePosition{ -5, 11, count })
        );

        count++;
    }

    std::cout << node_data.compile() << std::endl;
}