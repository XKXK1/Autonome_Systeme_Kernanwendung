//
// Created by Grages, Philip on 04.06.18.
//

#ifndef A_STAR_PATHCALCULATOR_H
#define A_STAR_PATHCALCULATOR_H

#include "JsonReader.h"
#include "AStar.h"
#include "../checkpoint.h"


class PathCalculator{
private:
    std::string _edge_path;
    std::string _node_path;
    std::list<Edge> _edges;
    std::map<const int,Node> _nodes;
public:
    PathCalculator(std::string node_path,std::string edge_path);
    std::vector<Checkpoint> getPath(float x_position, float y_position, int id);

};


#endif //A_STAR_PATHCALCULATOR_H
