#include <iostream>
#include "../sdk.h"

static int run_test() {
    NodeData node_data = NodeData();

    MemoryCell memory_cell = MemoryCell(&node_data);

    node_data.create<FLIPFLOP>(NodePosition{ 1, 5, 0 })
        .connect_to(memory_cell.input_node);

    memory_cell.output_node.connect_to(
        node_data.create<LED>(NodePosition{ 2, 5, 0 })
    );

    node_data.create<BUTTON>(NodePosition{ 3, 5, 0 })
        .connect_to(memory_cell.update_node);

    std::cout << node_data.compile() << std::endl;
}