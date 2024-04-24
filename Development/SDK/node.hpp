#pragma once
#include <vector>

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
	ANTENNA
};

struct NodePosition {
	char x;
	char y;
	char z;
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
};

struct NodeRef {
	std::vector<Node>* nodes;
	unsigned short node_id;

	NodeRef();
	NodeRef(std::vector<Node>* nodes_vector);

	Node* get();

	NodeRef& operator<<(const NodeRef& node);
	NodeRef& operator<<(const NodeVec& nodes);
	NodeRef& operator>>(const NodeRef& node);
	NodeRef& operator>>(const NodeVec& nodes);
};