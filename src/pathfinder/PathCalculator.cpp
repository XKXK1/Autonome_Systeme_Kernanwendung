//
// Created by Grages, Philip on 23.05.18.
//
#include "PathCalculator.h"

PathCalculator::PathCalculator(node_path, edge_path) : _node_path(node_path),_edge_path(edge_path){
}
vector<Checkpoint> PathCalculator::getPath(float x_position, float y_position, int id) {
    JsonReader json = JsonReader(_node_path,_edge_path);
    list<Edge> edges;
    map<const int,Node> nodes;
    json.createNodeEdgeMap(edges,nodes);
    Node node = nodes[id];

    vector<Checkpoint> checkpoints;
    AStar astar = AStar(edges, nodes);
    list<Node>* shortestPath = astar.getShortestPath(x_position,y_position,node);
    for(list<Node>::iterator it = shortestPath->begin(); it != shortestPath->end();++it){
        checkpoints.push_back(Checkpoint(it->getXPosition(),it->getYPosition()));
    }
    return checkpoints;
}

