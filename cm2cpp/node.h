#pragma once
#include <string>
#include <vector>
#include <map>

enum NodeTypes {
	NOR,
	AND,
	OR,
	XOR,
	BUTTON,
	FLIPFLOP,
	LED,
	SOUND,
	CONDUCTOR,
	CUSTOM,
	NAND,
	XNOR,
	RANDOM,
	TEXT,
	TILE,
	NODE,
	DELAY,
	ANTENNA,
	CONDUCTORV2
};

struct NodePosition {
	short x = -1;
	short y = -1;
	short z = -1;
};

struct NodeRef;
typedef std::vector<NodeRef> NodeVec;

struct Node {
	NodeTypes type;
	bool state;
	NodePosition position;

	std::vector<short> properties;

	NodeVec source;
	NodeVec destination;

	bool dont_optimize;
	unsigned int node_id;
};

struct SpecialBuildingNode {
	std::string building_type;
	NodePosition position;
	std::vector<float> cframe_rotation_matrix;
	std::map<unsigned char, unsigned int> connections;
};

struct SignNode {
	std::string text;

	std::string to_hex();
};

struct NodeData;

struct NodeRef {
	NodeData* node_data;
	unsigned int node_id;

	NodeRef();
	NodeRef(NodeData* node_data);

	Node* get();

	NodeRef& operator<<(const NodeRef& node);
	NodeRef& operator<<(const NodeVec& nodes);
	NodeRef& operator>>(const NodeRef& node);
	NodeRef& operator>>(const NodeVec& nodes);
};