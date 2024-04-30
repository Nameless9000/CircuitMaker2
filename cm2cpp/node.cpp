#include "node.h"
#include "data.h"
#include <stdexcept>
#include <iomanip>

NodeRef::NodeRef() : node_data(0), node_id(-1) {}
NodeRef::NodeRef(NodeData* node_datax) {
	node_data = node_datax;
	node_id = (unsigned short)(node_data->nodes.size() - 1);

	node_data->nodes.back().node_id = node_id; // make a copy for compilation
}

Node* NodeRef::get() {
	return &node_data->nodes.at(node_id);
}

NodeRef& NodeRef::operator>>(const NodeRef& node) {
	if (node.node_data == nullptr)
		throw std::invalid_argument("node is invalid");

	NodeRef node_copy = node;
	get()->destination.push_back(node);
	node_copy.get()->source.push_back(*this);

	return node_copy;
}

NodeRef& NodeRef::operator>>(const NodeVec& nodes) {
	for (NodeRef node : nodes) {
		if (node.node_data == nullptr)
			throw std::invalid_argument("node is invalid");

		get()->destination.push_back(node);
		node.get()->source.push_back(*this);
	}

	return *this;
}

NodeRef& NodeRef::operator<<(const NodeRef& node) {
	if (node.node_data == nullptr)
		throw std::invalid_argument("node is invalid");

	NodeRef node_copy = node;
	get()->source.push_back(node);
	node_copy.get()->destination.push_back(*this);

	return node_copy;
}

NodeRef& NodeRef::operator<<(const NodeVec& nodes) {
	for (NodeRef node : nodes) {
		if (node.node_data == nullptr)
			throw std::invalid_argument("node is invalid");

		get()->source.push_back(node);
		node.get()->destination.push_back(*this);
	}

	return *this;
}

SignNode::SignNode(std::string data) : text(data) {}

std::string SignNode::to_hex()
{
	if (!hex_data.empty())
		return hex_data;

	const char* hex_chars = "0123456789ABCDEF";

	std::string hex;
	for (unsigned char c : text) {
		hex.push_back(hex_chars[c >> 4]);
		hex.push_back(hex_chars[c & 15]);
	}

	hex_data = hex;
	return hex;
}
