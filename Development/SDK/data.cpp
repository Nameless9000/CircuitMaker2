#include <iostream>
#include "data.hpp"

std::string NodeData::compile(char max_x, char max_z) {
	char x = 0;
	char y = 0;
	char z = 0;

	int block_count = 0;
	int connection_count = 0;

	std::string blocks = "";
	std::string connections = "";

	unsigned short index = 0;
	for (Node node : nodes) {
		if (!blocks.empty()) blocks += ";";
		blocks += std::to_string(node.type); // id

		block_count++;

		if (node.state) { // state
			blocks += ",1";
		}
		else {
			blocks += ",";
		}

		blocks += ",";
		if (node.position.x == -1 && node.position.y == -1 && node.position.z == -1) { // position
			blocks += std::to_string(x) + ",";
			blocks += std::to_string(y) + ",";
			blocks += std::to_string(z);

			x++;
			if (x == max_x) {
				x = 0;
				z++;
				if (z == max_z) {
					z = 0;
					y++;
				}
			}
		}
		else {
			blocks += std::to_string(node.position.x) + ",";
			blocks += std::to_string(node.position.y) + ",";
			blocks += std::to_string(node.position.z);
		}

		// properties
		blocks += ",";

		std::string properties = "";
		for (short property : node.properties) {
			if (!properties.empty()) properties += "+";
			properties += std::to_string(property);
		}

		blocks += properties;

		for (NodeRef source_node : node.source) { // connections
			if (!connections.empty()) connections += ";";
			connections += std::to_string(source_node.node_id + 1) + "," + std::to_string(index + 1);
			connection_count++;
		}

		index++;
	}

	std::string save_string = blocks + "?" + connections;

	std::cout << "[Compile Stats] Raw: " << save_string.length() << " | Blocks: " << block_count << " | Connections : " << connection_count << "\n\n";

	return save_string;
}

#define INSTANTIATE_CREATE(T) template NodeRef NodeData::create<T>(NodePosition, bool, std::vector<short>)

template <NodeTypes T>
NodeRef NodeData::create(NodePosition position, bool state, std::vector<short> properties) {
	nodes.push_back({ T, state, position, properties, {}, {} });
	return NodeRef(&nodes);
};

// sorry...
INSTANTIATE_CREATE(NOR);
INSTANTIATE_CREATE(AND);
INSTANTIATE_CREATE(OR);
INSTANTIATE_CREATE(XOR);
INSTANTIATE_CREATE(BUTTON);
INSTANTIATE_CREATE(FLIPFLOP);
INSTANTIATE_CREATE(LED);
INSTANTIATE_CREATE(SOUND);
INSTANTIATE_CREATE(CONDUCTOR);
INSTANTIATE_CREATE(CUSTOM);
INSTANTIATE_CREATE(NAND);
INSTANTIATE_CREATE(XNOR);
INSTANTIATE_CREATE(RANDOM);
INSTANTIATE_CREATE(TEXT);
INSTANTIATE_CREATE(TILE);
INSTANTIATE_CREATE(NODE);
INSTANTIATE_CREATE(DELAY);
INSTANTIATE_CREATE(ANTENNA);