#pragma once
#include <string>
#include "node.hpp"

struct NodeData {
	std::vector<Node> nodes;

	std::string compile(char max_x = 5, char max_z = 5);

	template <NodeTypes T>
	NodeRef create(NodePosition position = { -1,-1,-1 }, bool state = false, std::vector<short> properties = {});
};