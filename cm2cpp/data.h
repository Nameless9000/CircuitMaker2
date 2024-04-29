#pragma once
#include <string>
#include "node.h"

struct NodeData {
	std::vector<Node> nodes;

	std::string compile(bool no_debug = false, bool compile_for_speed = false, bool optimize_positions = false, short max_x = 5, short max_z = 5);

	template <NodeTypes T>
	NodeRef create(NodePosition position = {}, bool dont_optimize = false, bool state = false, std::vector<short> properties = {});

	void import_savestring(std::string savestring);
};