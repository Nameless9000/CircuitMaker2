#include "data.h"
#include <iostream>
#include <algorithm>

static bool contains_loop(NodeVec from, NodeVec to) {
	for (NodeRef node1 : from) {
		for (NodeRef node2 : to) {
			if (node1.node_id == node2.node_id)
				return true;
		}
	}

	return false;
}

static bool compare_connections(Node n1, Node n2) {
	return (n1.destination.size() + n1.source.size()) > (n2.destination.size() + n2.source.size());
}

template <typename T>
static std::string to_string_nozero(T number) {
	if (number == 0)
		return "";

	return std::to_string(number);
}

static NodeData preprocess_data(NodeData* input) {
	NodeData new_data = NodeData();

	new_data.special_buildings = input->special_buildings;
	new_data.signs = input->signs;

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
			}
			else if (node.destination.size() == 1) {
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

	// high connections are first, reducing size
	std::sort(new_data.nodes.begin(), new_data.nodes.end(), compare_connections);

	return new_data;
}

std::string NodeData::compile(bool no_debug, bool compile_for_speed, bool optimize_positions, short max_x, short max_z) {
	NodeData processed_data = preprocess_data(this);

	short x = 0;
	short y = 0;
	short z = 0;

	int block_count = 0;
	std::string blocks = "";

	std::map<unsigned int, unsigned int> node_id_substitution;

	for (Node node : processed_data.nodes) {
		if (!blocks.empty()) blocks += ";";

		if (compile_for_speed) {
			switch (node.type)
			{
			case OR:
			case LED:
				node.type = NODE;
			}
		}
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
			blocks += to_string_nozero(x) + ",";
			blocks += to_string_nozero(y) + ",";
			blocks += to_string_nozero(z);

			if (!optimize_positions) {
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
		}
		else {
			blocks += to_string_nozero(node.position.x) + ",";
			blocks += to_string_nozero(node.position.y) + ",";
			blocks += to_string_nozero(node.position.z);
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
	int connection_count = 0;
	std::string connections = "";

	unsigned short index = 1;
	for (Node node : processed_data.nodes) {
		for (NodeRef destination_node : node.destination) {
			unsigned short destination = node_id_substitution[destination_node.node_id];
			if (destination == NULL)
				continue;

			if (!connections.empty()) connections += ";";

			connections += to_string_nozero(index) + "," + to_string_nozero(destination);
			connection_count++;
		}

		index++;
	}

	// handle special buildings
	int special_building_count = 0;
	std::string special_buildings = "";
	for (SpecialBuildingNode node : processed_data.special_buildings) {
		if (!special_buildings.empty()) special_buildings += ";";

		special_buildings += node.building_type;
		special_building_count++;

		if (!(node.position.x == -1 && node.position.y == -1 && node.position.z == -1)) {
			special_buildings += ",";
			special_buildings += std::to_string(node.position.x) + ",";
			special_buildings += std::to_string(node.position.y) + ",";
			special_buildings += std::to_string(node.position.z);
		}

		if (!node.cframe_rotation_matrix.empty()) {
			for (float rotation_matrix : node.cframe_rotation_matrix) {
				special_buildings += ",";

				std::string str = std::to_string(rotation_matrix);
                str.erase(str.find_last_not_of('0') + 1, std::string::npos);
                str.erase(str.find_last_not_of('.') + 1, std::string::npos);

				special_buildings += str;
			}
		}

		if (node.connections.empty())
			continue;

		for (std::string connection : node.connections) {
            special_buildings += ",";
            special_buildings += connection;
		}
	}

	// handle signs
	int sign_count = 0;
	std::string signs = "";
	for (SignNode sign : processed_data.signs) {
		if (!signs.empty()) signs += ";";

		signs += sign.to_hex();
	}

	std::string save_string = blocks + "?" + connections + "?" + special_buildings + "?" + signs;

	if (!no_debug) {
		std::cout
			<< "[Compile Stats] Raw: " << save_string.length()
			<< " | Blocks: " << block_count << " (" << blocks.length()
			<< ") | Connections: " << connection_count << " (" << connections.length()
			<< ") | Special Buildings: " << special_building_count << " (" << special_buildings.length()
			<< ") | Signs: " << sign_count << " (" << signs.length() << ")"
			<< std::endl;
	}

	return save_string;
}

#define INSTANTIATE_CREATE(T) template NodeRef NodeData::create<T>(NodePosition, bool, bool, std::vector<short>)

template <NodeTypes T>
NodeRef NodeData::create(NodePosition position, bool dont_optimize, bool state, std::vector<short> properties) {
	nodes.push_back({ T, state, position, properties, {}, {}, dont_optimize });
	return NodeRef(this);
};
NodeRef NodeData::create(NodeTypes type, NodePosition position, bool dont_optimize, bool state, std::vector<short> properties) {
    nodes.push_back({ type, state, position, properties, {}, {}, dont_optimize });
    return NodeRef(this);
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
INSTANTIATE_CREATE(CONDUCTORV2);