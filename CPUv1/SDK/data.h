#pragma once
#include <string> 
#include "node.h"

struct NodeData {
	std::vector<Node> nodes;

	std::string compile() {
		char x = 0;
		char y = 0;
		char z = 0;

		std::string blocks = "";
		std::string connections = "";

		unsigned short index = 0;
		for (Node node : nodes) {
			if (!blocks.empty()) blocks += ";";
			blocks += std::to_string(node.type); // id

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
				if (x > 10) {
					x = 0;
					z++;
					if (z > 10) {
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
			}
			
			index++;
		}

		return blocks + "?" + connections;
	}

	NodeRef create_nor(NodePosition position = { -1,-1,-1 }, bool state = false) {
		nodes.push_back({ NOR, state, position, {}, {}, {} });
		return NodeRef(&nodes);
	};

	NodeRef create_and(NodePosition position = { -1,-1,-1 }, bool state = false) {
		nodes.push_back({ AND, state, position, {}, {}, {} });
		return NodeRef(&nodes);
	};

	NodeRef create_or(NodePosition position = { -1,-1,-1 }, bool state = false) {
		nodes.push_back({ OR, state, position, {}, {}, {} });
		return NodeRef(&nodes);
	};

	NodeRef create_xor(NodePosition position = { -1,-1,-1 }, bool state = false) {
		nodes.push_back({ XOR, state, position, {}, {}, {} });
		return NodeRef(&nodes);
	};

	NodeRef create_button(NodePosition position = { -1,-1,-1 }, bool state = false) {
		nodes.push_back({ BUTTON, state, position, {}, {}, {} });
		return NodeRef(&nodes);
	};

	NodeRef create_flipflop(NodePosition position = { -1,-1,-1 }, bool state = false) {
		nodes.push_back({ FLIPFLOP, state, position, {}, {}, {} });
		return NodeRef(&nodes);
	};

	NodeRef create_led(NodePosition position = { -1,-1,-1 }, bool state = false, std::vector<short> properties = {}) {
		nodes.push_back({ LED, state, position, properties, {}, {} });
		return NodeRef(&nodes);
	};

	NodeRef create_sound(NodePosition position = { -1,-1,-1 }, bool state = false, std::vector<short> properties = {}) {
		nodes.push_back({ SOUND, state, position, properties, {}, {} });
		return NodeRef(&nodes);
	};

	NodeRef create_conductor(NodePosition position = { -1,-1,-1 }, bool state = false) {
		nodes.push_back({ CONDUCTOR, state, position, {}, {}, {} });
		return NodeRef(&nodes);
	};

	NodeRef create_custom(NodePosition position = { -1,-1,-1 }, bool state = false, std::vector<short> properties = {}) {
		nodes.push_back({ CUSTOM, state, position, properties, {}, {} });
		return NodeRef(&nodes);
	};

	NodeRef create_nand(NodePosition position = { -1,-1,-1 }, bool state = false) {
		nodes.push_back({ NAND, state, position, {}, {}, {} });
		return NodeRef(&nodes);
	};

	NodeRef create_xnor(NodePosition position = { -1,-1,-1 }, bool state = false) {
		nodes.push_back({ XNOR, state, position, {}, {}, {} });
		return NodeRef(&nodes);
	};

	NodeRef create_random(NodePosition position = { -1,-1,-1 }, bool state = false, std::vector<short> properties = {}) {
		nodes.push_back({ RANDOM, state, position, properties, {}, {} });
		return NodeRef(&nodes);
	};

	NodeRef create_text(NodePosition position = { -1,-1,-1 }, bool state = false, std::vector<short> properties = {}) {
		nodes.push_back({ TEXT, state, position, properties, {}, {} });
		return NodeRef(&nodes);
	};

	NodeRef create_tile(NodePosition position = { -1,-1,-1 }, bool state = false, std::vector<short> properties = {}) {
		nodes.push_back({ TILE, state, position, properties, {}, {} });
		return NodeRef(&nodes);
	};

	NodeRef create_node(NodePosition position = { -1,-1,-1 }, bool state = false) {
		nodes.push_back({ NODE, state, position, {}, {}, {} });
		return NodeRef(&nodes);
	};

	NodeRef create_delay(NodePosition position = { -1,-1,-1 }, bool state = false, std::vector<short> properties = {}) {
		nodes.push_back({ DELAY, state, position, properties, {}, {} });
		return NodeRef(&nodes);
	};

	NodeRef create_antenna(NodePosition position = { -1,-1,-1 }, bool state = false, std::vector<short> properties = {}) {
		nodes.push_back({ ANTENNA, state, position, properties, {}, {} });
		return NodeRef(&nodes);
	};
};