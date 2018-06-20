#include "AStar.h"
#include "iostream"
#include "ros/ros.h"

using namespace std;

AStar::AStar(list<Edge> edges, map<const int, Node> nodes) :_edges(edges), _nodes(nodes) {}

list<Node> AStar::getShortestPath(float x_position, float y_position, Node destination) {
	cout << 1;
	ROS_INFO("getFirstNode");
	Node firstNode = getClosestNode(x_position, y_position);
	list<Edge> connectedEdges;
	list<Edge> openList;
	list<Edge> closedList;
	
	ROS_INFO("Start propagation");
	openList = propagationThrouNodes(firstNode, openList,closedList, destination);
	ROS_INFO("Finished Propagation");
	list<Node> return_nodes = edgesToNodes(openList,destination);
	return return_nodes;
}

list<Edge> AStar::propagationThrouNodes(Node firstNode, list<Edge> &openList, list<Edge> closedList, Node destination) {
	closedList = openList;
	if (firstNode.getId() != destination.getId()) {
		list<Edge> connectedEdges;
		cout<< destination.getId() << " : " << firstNode.getId();
		getConnectedEdges(connectedEdges, firstNode);
		if (connectedEdges.empty()) {
			return closedList;
		}
		for (list<Edge>::iterator it = connectedEdges.begin(); it != connectedEdges.end(); ++it) {
			_edges.remove(*it);
		}
		ROS_INFO("sorting");
		cout << connectedEdges.size();
		connectedEdges.sort([=](Edge &a, Edge &b) {
			Node node1;
			ROS_INFO("test1");
			cout << "A Edge: (" << a.getNode1().getId() << "," << a.getNode2().getId() << ")"<< endl;
			cout << "FirstNode: " << firstNode.getId() << endl;			
			if (a.getNode1().getId() == firstNode.getId())
				node1 = a.getNode2();
			else
				node1 = a.getNode1();

			ROS_INFO("test2");
			Node node2;
			if (b.getNode1().getId() == firstNode.getId())
				node2 = b.getNode2();
			else
				node2 = b.getNode1();

			ROS_INFO("test3");

			return (getDistance(node1, destination) + a.getWeight()) <
				   (getDistance(node2, destination) + b.getWeight());
		});
		ROS_INFO("done");
		list<Edge> temp = openList;
		temp.push_front(Edge(Node(), Node(), 0));
		for (list<Edge>::iterator it = connectedEdges.begin(); it != connectedEdges.end(); ++it) {
			temp.pop_front();
			temp.push_front(*it);
			if (it->getNode1().getId() == firstNode.getId())
				firstNode = it->getNode2();
			else
				firstNode = it->getNode1();
			list<Edge> closedList2 = propagationThrouNodes(firstNode, temp, closedList, destination);
			if (closedList.empty() || (closedList.front().getNode1().getId() != destination.getId() &&
				closedList.front().getNode2().getId() != destination.getId()))
				closedList = closedList2;
			else if ((closedList2.front().getNode1().getId() == destination.getId() || closedList2.front().getNode2().getId() == destination.getId()) && getSmallesWeight(closedList, closedList2))
				closedList = closedList2;
		}
	}
	cout<<"throu";
	return closedList;
}


Node AStar::getClosestNode(float x_position, float y_position) {
	map<string, Node>::iterator it;
	float shortestDistance = 0;
	Node shortestNode(0,0,0);
	for(map<const int,Node>::iterator it = _nodes.begin(); it != _nodes.end(); ++it) {
		Node node = it->second;
		float currentDistance = sqrt(powf(node.getXPosition() - x_position,2) + powf(node.getYPosition() - y_position,2)) ;
		if (shortestDistance == 0 || shortestDistance > currentDistance) {
			shortestDistance = currentDistance;
			shortestNode = node;
		}
	}
	return shortestNode;
}

void AStar::getConnectedEdges(list<Edge>& connectedEdges, Node start) {
	for (list<Edge>::iterator it = _edges.begin(); it != _edges.end(); ++it) {
		if (it->getNode1().getId() == start.getId() || it->getNode2().getId() == start.getId()) {
			connectedEdges.push_front(*it);
		}
	}
}

bool AStar::contains(list<Edge> edges, Edge edge) {
	bool contained = false;
	for (list<Edge>::iterator it = edges.begin(); it != edges.end(); ++it) {
		if (it->getWeight() == edge.getWeight()) { contained = true; }
	}
	return contained;
}

float AStar::getDistance(Node node, Node destination) {
	return sqrt(powf(node.getXPosition() - destination.getXPosition(), 2) + powf(node.getYPosition() - destination.getYPosition(), 2));
}

list<Node> AStar::edgesToNodes(list<Edge> edges,Node start) {
	list<Node> nodes = {};
	nodes.push_front(start);
	Node tmp = start;
	for (list<Edge>::iterator it = edges.begin(); it != edges.end();++it) {
		if (it->getNode1() == tmp) {
			nodes.push_front(it->getNode2());
			tmp = it->getNode2();
		} else {
			nodes.push_front(it->getNode1());
			tmp = it->getNode1();
		}
	}
	return nodes;
}

bool AStar::getSmallesWeight(list<Edge> edge1, list<Edge> edge2){
	int weightOne = 0;
	int weightTwo = 0;
	for(list<Edge>::iterator it = edge1.begin(); it != edge1.end();++it)
		weightOne += it->getWeight();
	for(list<Edge>::iterator it = edge2.begin(); it != edge2.end();++it)
		weightTwo += it->getWeight();
	return weightOne > weightTwo;
}
