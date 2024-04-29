#pragma once
#include "data.h"

namespace Arithmetic {
	struct FullAdder {
		NodeVec input_bits1;
		NodeVec input_bits2;
		NodeVec output_bits;
		NodeRef carry_bit_out;
		NodeRef carry_bit_in;

		FullAdder(NodeData* node_data, unsigned char bits = 8);
	};
}