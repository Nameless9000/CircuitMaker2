#include "arithmetic.h"

Arithmetic::FullAdder::FullAdder(NodeData* node_data, unsigned char bits) {
	for (unsigned char _ = 0; _ < bits; _++) {
		NodeRef output = node_data->create<XOR>();
		output_bits.push_back(output);

		NodeRef carry = node_data->create<OR>();

		NodeRef and_gate1 = node_data->create<AND>();
		NodeRef and_gate2 = node_data->create<AND>();
		NodeRef xor_gate = node_data->create<XOR>();

		NodeRef input1 = node_data->create<LED>();
		input_bits1.push_back(input1);
		NodeRef input2 = node_data->create<LED>();
		input_bits2.push_back(input2);
		NodeRef carry_buf = node_data->create<LED>({}, true);

		input1 >> NodeVec{ xor_gate, and_gate2 };
		input2 >> NodeVec{ xor_gate, and_gate2 };

		if (carry_bit_out.node_data != nullptr)
			carry_bit_out >> carry_buf;

		carry_buf >> NodeVec{ output, and_gate1 };
		if (carry_bit_in.node_data == nullptr)
			carry_bit_in = carry_buf;
		xor_gate >> NodeVec{ output, and_gate1 };

		carry << NodeVec{ and_gate1, and_gate2 };
		carry_bit_out = carry;
	}
}
