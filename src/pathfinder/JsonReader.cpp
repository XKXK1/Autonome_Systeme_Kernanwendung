#include "JsonReader.h"
#include <iostream>

using json = nlohmann::json;
using namespace std;

JsonReader::JsonReader(std::string node_path, std::string edge_path)
{
	_node_path = node_path;
	_edge_path = edge_path;
}

void JsonReader::createNodeEdgeMap(list<Edge>& edges, map<const int, Node>& nodes) {
	parseNodes(nodes);
	parseEdges(edges, nodes);

}

void JsonReader::parseNodes(map<const int, Node>& nodes) {
	std::ifstream inputFileStream(_node_path);

	for (std::string line; getline(inputFileStream, line);) {
		json jsonObject = json::parse(line);
		Node node(jsonObject["id"], jsonObject["x_position"], jsonObject["y_position"]);
		node.z_rotation = jsonObject["z_rotation"];
		node.w_rotation = jsonObject["w_rotation"];
		nodes[jsonObject["id"]] = node;
	}
}

void JsonReader::parseEdges(list<Edge>& edges, map<const int, Node>& nodes) {
	std::ifstream inputFileStream(_edge_path);

	for (std::string line; getline(inputFileStream, line);) {
		json jsonObject = json::parse(line);
		Edge edge(nodes[jsonObject["id_node_one"]], nodes[jsonObject["id_node_two"]], jsonObject["weight"]);
		edges.push_front(edge);
	}
}