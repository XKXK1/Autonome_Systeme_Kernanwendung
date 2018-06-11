#include "Edge.h"

Edge::Edge(Node node1, Node node2, int weight) : _node1(node1), _node2(node2), _weight(weight) {}

bool Edge::operator==(const Edge& e) const {
	return ((_node1 == e._node1 || _node1 == e._node2) && (_node2 == e._node1 || _node2 == e._node2));
}

int Edge::getWeight() {
	return _weight;
}

Node Edge::getNode1() {
	return _node1;
}

Node Edge::getNode2() {
	return _node2;
}