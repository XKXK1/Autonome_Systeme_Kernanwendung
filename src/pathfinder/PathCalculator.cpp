//
// Created by Grages, Philip on 23.05.18.
//
#include <ros/ros.h>
#include "PathCalculator.h"


using namespace std;

PathCalculator::PathCalculator(string node_path, string edge_path) : _node_path(node_path),_edge_path(edge_path){
    JsonReader json = JsonReader(_node_path, _edge_path);
    json.createNodeEdgeMap(_edges,_nodes);

    if(_edges.size() == 0){
        ROS_ERROR("Failed to load edges file");
    }
    if(_nodes.size() == 0){
        ROS_ERROR("Failed to load node file");
    }
}
vector<Checkpoint> PathCalculator::getPath(float x_position, float y_position, int id) {
    Node node = _nodes[id];

    vector<Checkpoint> checkpoints;
    ROS_INFO("Starting A Star algorithm");
    AStar astar = AStar(_edges, _nodes);
    ROS_INFO("Returning shortest path");
    list<Node>* shortestPath = astar.getShortestPath(x_position,y_position,node);
    ROS_INFO("Building checkpoints vector");
    for(list<Node>::iterator it = shortestPath->begin(); it != shortestPath->end();++it){
	    Checkpoint ncp(it->getXPosition(),it->getYPosition());
        checkpoints.push_back(ncp);
    }
    return checkpoints;
}

