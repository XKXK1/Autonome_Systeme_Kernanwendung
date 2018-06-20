#ifndef ASTAR_H
#define ASTAR_H

#include <list>
#include <map>
#include <math.h>

#include "Edge.h"
#include "Node.h"

class AStar {
private:
	std::list<Edge> _edges;
	std::map<const int, Node> _nodes;
	Node getClosestNode(float x_position, float y_position);
	void getConnectedEdges(std::list<Edge>& connectedEdges, Node node);	
	bool contains(std::list<Edge> edges, Edge edge);
	std::list<Edge> propagationThrouNodes(Node startNode, std::list<Edge> &openList, std::list<Edge> closedList, Node destination);
	float getDistance(Node node, Node destination);
	std::list<Node> edgesToNodes(std::list<Edge> openList, Node start);

public:
	AStar(std::list<Edge> edges, std::map<const int, Node> nodes);
	std::list<Node> getShortestPath(float x_position, float y_position, Node destination);

    bool getSmallesWeight(std::list<Edge> edge1, std::list<Edge> edge2);
};


#endif
