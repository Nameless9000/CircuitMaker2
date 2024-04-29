#include "display.h"

Display::SevenSegmentDecimal::SevenSegmentDecimal(NodeData* node_data) {
	a = node_data->create<LED>();
	b = node_data->create<LED>();
	c = node_data->create<LED>();
	d = node_data->create<LED>();
	e = node_data->create<LED>();
	f = node_data->create<LED>();
	g = node_data->create<LED>();

	NodeRef zero = node_data->create<NOR>();
	for (unsigned char i = 0; i < 9; i++) {
		bits[i] = node_data->create<LED>();
		bits[i] >> zero;
	}

	zero >> NodeVec{ a, b, c, d, e, f };
	bits[0] >> NodeVec{ b, c };
	bits[1] >> NodeVec{ a, b, g, e, d };
	bits[2] >> NodeVec{ a, b, g, c, d };
	bits[3] >> NodeVec{ f, g, b, c };
	bits[4] >> NodeVec{ a, f, g, c, d };
	bits[5] >> NodeVec{ a, f, g, c, d, e };
	bits[6] >> NodeVec{ a, b, c };
	bits[7] >> NodeVec{ a, b, c, d, e, f, g };
	bits[8] >> NodeVec{ g, f, a, b, c };
}