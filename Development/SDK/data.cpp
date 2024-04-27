#include <iostream>
#include <map> 
#include "data.hpp"

static bool contains_loop(NodeVec from, NodeVec to) {
	for (NodeRef node1 : from) {
		for (NodeRef node2 : to) {
			if (node1.node_id == node2.node_id)
				return true;
		}
	}

	return false;
}

static NodeData preprocess_data(NodeData* input) {
	NodeData new_data = NodeData();

	for (Node node : input->nodes) {
		if (node.dont_optimize || contains_loop(node.source, node.destination)) {
			goto ADD_NODE;
		}
		
		if (
			node.source.size() == 0 && (
				node.type != FLIPFLOP &&
				node.type != BUTTON &&
				node.type != ANTENNA &&
				node.type != RANDOM
				) ||
			node.destination.size() == 0 && (
				node.type != LED &&
				node.type != SOUND
				)
			)
			continue;

		switch (node.type) {
			case NODE:
			case CUSTOM:
			case TILE:
			case TEXT:
			case LED:
			case OR:
				if (node.source.size() == 1) {
					for (NodeRef dnode : node.destination) {
						node.source.front() >> dnode;
					}
					continue;
				} else if (node.destination.size() == 1) {
					for (NodeRef snode : node.source) {
						node.destination.front() << snode;
					}
					continue;
				}
				[[fallthrough]];
			case AND:
			case XOR:
			case BUTTON:
				if (node.source.size() == 1 && node.destination.size() == 1) {
					node.source.front() >> node.destination.front();
					continue;
				}
		}

	ADD_NODE:

		new_data.nodes.push_back(node);
	}

	return new_data;
}

std::string NodeData::compile(char max_x, char max_z) {
	NodeData processed_data = preprocess_data(this);

	char x = 0;
	char y = 0;
	char z = 0;

	int block_count = 0;
	int connection_count = 0;

	std::string blocks = "";
	std::string connections = "";

	std::map<unsigned short, unsigned short> node_id_substitution;

	for (Node node : processed_data.nodes) {
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

		// map the new node_id
		node_id_substitution[node.node_id] = block_count;
	}

	// handle connections
	unsigned short index = 1;
	for (Node node : processed_data.nodes) {
		for (NodeRef destination_node : node.destination) {
			unsigned short destination = node_id_substitution[destination_node.node_id];
			if (destination == NULL)
				continue;

			if (!connections.empty()) connections += ";";

			connections += std::to_string(index) + "," + std::to_string(destination);
			connection_count++;
		}

		index++;
	}

	std::string save_string = blocks + "?" + connections;

	std::cout << "[Compile Stats] Raw: " << save_string.length() << " | Blocks: " << block_count << " | Connections : " << connection_count << "\n\n";

	return save_string;
}

#define INSTANTIATE_CREATE(T) template NodeRef NodeData::create<T>(NodePosition, bool, bool, std::vector<short>)

template <NodeTypes T>
NodeRef NodeData::create(NodePosition position, bool dont_optimize, bool state, std::vector<short> properties) {
	nodes.push_back({ T, state, position, properties, {}, {}, dont_optimize });
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