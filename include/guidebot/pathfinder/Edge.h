#pragma once
#include "Node.h"

class Edge {
	Node _node1;
	Node _node2;
	int _weight;
public:
	Edge(Node node1, Node node2, int weight);

	Node getNode1();
	Node getNode2();
	int getWeight();
	bool operator == (const Edge& e) const;
};