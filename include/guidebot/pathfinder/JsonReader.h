#pragma once
#include <string>
#include <list>
#include <iterator>
#include <fstream>
#include "json.hpp"
#include <map>

#include "Node.h"
#include "Edge.h"
class JsonReader
{
private:
	std::string _node_path;
	std::string _edge_path;

	void parseNodes(std::map<const int, Node>& nodeMap);
	void parseEdges(std::list<Edge>& edges, std::map<const int, Node>& nodeMap);

public:
	JsonReader(std::string node_path, std::string edge_path);
	
	void createNodeEdgeMap(std::list<Edge>& edges, std::map<const int, Node>& nodeMap);

};

