#include <stdexcept>
#include "node.hpp"

NodeRef::NodeRef() : nodes(0), node_id(-1) {}
NodeRef::NodeRef(std::vector<Node>* nodes_vector) {
	nodes = nodes_vector;
	node_id = (unsigned short)(nodes->size() - 1);
}

Node* NodeRef::get() {
	return &nodes->at(node_id);
}

NodeRef NodeRef::connect_to(NodeRef node) {
	if (node.nodes == nullptr)
		throw std::invalid_argument("node is invalid");

	get()->destination.push_back(node);
	node.get()->source.push_back(*this);

	return *this;
}