#include "fun.hpp"

void Fun::generate_text(NodeData* node_data, std::string text, bool wordwrap, unsigned short wordwrap_size) {
    char x = 0;
    char z = 0;

    for (char& code : text) {
        if ((wordwrap && x >= wordwrap_size && code == 32) || code == 10) {
            x = 0;
            z += 1;
            continue;
        }

        if (code < 32 && code > 126)
            code = 32;

        node_data->create<TEXT>(NodePosition{ x, 0, z }, true, false, { code });
        x++;
    }
}
