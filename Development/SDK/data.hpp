#pragma once
#include <string>
#include "node.hpp"

struct NodeData {
	std::vector<Node> nodes;

	std::string compile(bool compile_for_speed = false, short max_x = 5, short max_z = 5);

	template <NodeTypes T>
	NodeRef create(NodePosition position = {}, bool dont_optimize = false, bool state = false, std::vector<short> properties = {});
};