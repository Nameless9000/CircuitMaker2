#include "save_data.h"
#include <sstream>
#include <string>
#include <vector>

SaveData::SaveString::SaveString(std::string save_string) : data(save_string) {}

void SaveData::SaveString::import_string(NodeData* node_data) {
    node_data->nodes.clear();
    node_data->special_buildings.clear();
    node_data->signs.clear();

    std::stringstream ss(data);
    std::string item;

    std::vector<NodeRef> blocks;

    // Load blocks
    std::getline(ss, item, '?');
    std::stringstream blocks_stream(item);
    while (std::getline(blocks_stream, item, ';')) {
        std::stringstream blocks_stream(item);
        std::vector<std::string> blocks_values;

        while (std::getline(blocks_stream, item, ',')) {
            blocks_values.push_back(item);
        }

        NodeTypes type = static_cast<NodeTypes>(std::stoi(blocks_values[0]));

        bool state = false;
        if (!blocks_values[1].empty()) {
            state = std::stoi(blocks_values[1]);
        }

        NodePosition position = { 0, 0, 0 };
        
        if (!blocks_values[2].empty()) {
            position.x = static_cast<short>(std::stoi(blocks_values[2]));
        }
        if (!blocks_values[3].empty()) {
            position.y = static_cast<short>(std::stoi(blocks_values[3]));
        }
        if (!blocks_values[4].empty()) {
            position.z = static_cast<short>(std::stoi(blocks_values[4]));
        }

        std::vector<short> properties;
        if (blocks_values.size() == 6 && !blocks_values[5].empty()) {
            std::stringstream properties_stream(blocks_values[5]);
            while (std::getline(properties_stream, item, '+')) {
                properties.push_back(std::stoi(item));
            }
        }

        blocks.push_back(node_data->create(type, position, true, state, properties));
    }

    // Load connections
    std::getline(ss, item, '?');
    std::stringstream connections_stream(item);
    while (std::getline(connections_stream, item, ';')) {
        std::stringstream connections_stream(item);
        std::vector<int> connection_values;

        while (std::getline(connections_stream, item, ',')) {
            connection_values.push_back(std::stoi(item));
        }

        blocks[connection_values[0] - 1] << blocks[connection_values[1] - 1];
    }

    // Load special buildings
    std::getline(ss, item, '?');
    std::stringstream buildings_stream(item);
    while (std::getline(buildings_stream, item, ';')) {
        std::stringstream building_stream(item);

        std::vector<std::string> building_values;
        while (std::getline(building_stream, item, ',')) {
            building_values.push_back(item);
        }

        SpecialBuildingNode building;
        building.building_type = building_values[0];

        NodePosition position = { 0, 0, 0 };

        if (!building_values[1].empty()) {
            position.x = static_cast<short>(std::stoi(building_values[1]));
        }
        if (!building_values[2].empty()) {
            position.y = static_cast<short>(std::stoi(building_values[2]));
        }
        if (!building_values[3].empty()) {
            position.z = static_cast<short>(std::stoi(building_values[3]));
        }
        building.position = position;

        for (int i = 4; i < 12; ++i) {
            float value = 0;
            if (!building_values[i].empty()) {
                value = std::stof(building_values[i]);
            }
            building.cframe_rotation_matrix.push_back(value);
        }

        if (building_values.size() > 12) {
            building.connections = std::vector<std::string>(building_values.begin() + 12, building_values.end());
        }

        node_data->special_buildings.push_back(building);
    }

    // Load signs
    std::getline(ss, item, '?');
    std::stringstream signs_stream(item);
    while (std::getline(signs_stream, item, ';')) {
        SignNode sign(item);
        node_data->signs.push_back(sign);
    }
}