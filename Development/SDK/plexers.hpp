#pragma once
#include "data.hpp"

namespace Plexers {
    struct Decoder {
        std::vector<NodeRef> input_bits;
        std::vector<NodeRef> output_bits;

        Decoder();
        Decoder(NodeData* node_data, unsigned char data_bits);
    };
}