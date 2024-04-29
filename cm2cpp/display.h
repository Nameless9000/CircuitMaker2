#pragma once
#include "data.h"

namespace Display {
	struct SevenSegmentDecimal {
		NodeRef a;
		NodeRef b;
		NodeRef c;
		NodeRef d;
		NodeRef e;
		NodeRef f;
		NodeRef g;
		NodeRef bits[9];

		SevenSegmentDecimal(NodeData* node_data);
	};
}