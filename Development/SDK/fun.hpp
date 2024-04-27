#pragma once
#include "data.hpp"

namespace Fun {
	void generate_text(NodeData* node_data, std::string text, bool wordwrap = true, unsigned short wordwrap_size = 32);
}