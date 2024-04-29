#pragma once
#include "data.hpp"

namespace Plexers {
    struct Decoder {
        NodeVec input_bits;
        NodeVec output_bits;

        Decoder();
        Decoder(NodeData* node_data, unsigned char data_bits);
    };
}