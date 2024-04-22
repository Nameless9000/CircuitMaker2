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

class NodeRef;

struct Node {
	NodeTypes type;
	bool state;
	NodePosition position;

	std::vector<short> properties;

	std::vector<NodeRef> source;
	std::vector<NodeRef> destination;
};

class NodeRef {
	std::vector<Node>* nodes;
public:
	unsigned short node_id;

	NodeRef() : nodes(0), node_id(-1) {}
	NodeRef(std::vector<Node>* nodes_vector) {
		nodes = nodes_vector;
		node_id = (unsigned short)(nodes->size() - 1);
	}

	Node* get() {
		return &nodes->at(node_id);
	}

	void connect_to(NodeRef node) {
		get()->destination.push_back(node);
		node.get()->source.push_back(*this);
	}
};