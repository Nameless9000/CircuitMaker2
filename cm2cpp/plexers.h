#pragma once
#include "data.h"

namespace Plexers {
    struct Decoder {
        NodeVec input_bits;
        NodeVec output_bits;

        Decoder();
        Decoder(NodeData* node_data, unsigned char data_bits);
    };
}