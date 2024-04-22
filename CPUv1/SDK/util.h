#pragma once
#include "data.h"

struct Decoder {
    std::vector<NodeRef> input_bits;
    std::vector<NodeRef> output_bits;

    Decoder() : input_bits({}), output_bits({}) {};
	Decoder(NodeData* node_data, unsigned char data_bits) {
        std::vector<NodeRef> nor_gates;

        for (unsigned char _ = 0; _ < data_bits; _++) {
            NodeRef input = node_data->create<LED>();
            NodeRef nor = node_data->create<NOR>();

            input.connect_to(nor);

            input_bits.push_back(input);
            nor_gates.push_back(nor);
        }

        for (int counter = 0; counter < 1 << data_bits; counter++) {
            NodeRef and_gate = node_data->create<AND>();
            output_bits.push_back(and_gate);

            for (unsigned char idx = 0; idx < data_bits; idx++) {
                if ((counter >> idx & 1) == 1)
                    input_bits.at(idx).connect_to(and_gate);
                else
                    nor_gates.at(idx).connect_to(and_gate);
            }
        }
	}
};