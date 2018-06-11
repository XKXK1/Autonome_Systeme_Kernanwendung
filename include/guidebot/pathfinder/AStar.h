#pragma once
#include <list>
#include <map>
#include <math.h>

#include "Edge.h"
#include "Node.h"

using namespace std;

class AStar {
private:
	list<Edge> _edges;
	map<const int, Node> _nodes;
	Node getClosestNode(float x_position, float y_position);
	void getConnectedEdges(list<Edge>& connectedEdges, Node node);
	bool contains(list<Edge> edges, Edge edge);
	list<Edge> propagationThrouNodes(Node startNode, list<Edge> &openList, list<Edge> closedList, Node destination);
	float getDistance(Node node, Node destination);
	list<Node> edgesToNodes(list<Edge> openList, Node start);

public:
	AStar(list<Edge> edges, map<const int, Node> nodes);
	list<Node>* getShortestPath(float x_position, float y_position, Node destination);

    bool getSmallesWeight(list<Edge> edge1, list<Edge> edge2);
};