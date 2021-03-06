//
// Created by Grages, Philip on 23.05.18.
//
#include <ros/ros.h>
#include <iostream>
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
    vector<Checkpoint> checkpoints;
    for(int i = 0; i < _nodes.size(); i++){
        if(_nodes[i].getId() == id){
            Checkpoint ncp(_nodes[i].getXPosition(),_nodes[i].getYPosition(), _nodes[i].z_rotation, _nodes[i].w_rotation);
            checkpoints.push_back(ncp);
            return checkpoints;
        }
    }
}

/*
vector<Checkpoint> PathCalculator::getPath(float x_position, float y_position, int id) {
    cout << "ID: " << id << " | Size: " << _nodes.size() << std::endl;
    Node node = _nodes[id];



    vector<Checkpoint> checkpoints;
    ROS_INFO("Starting A Star algorithm");
    AStar astar = AStar(_edges, _nodes);
    ROS_INFO("Returning shortest path");
    list<Node> shortestPath = astar.getShortestPath(x_position,y_position,node);
    ROS_INFO("Building checkpoints vector");
    for(list<Node>::iterator it = shortestPath.begin(); it != shortestPath.end();++it){
	    Checkpoint ncp(it->getXPosition(),it->getYPosition());
        checkpoints.push_back(ncp);
    }
    return checkpoints;
}
*/

