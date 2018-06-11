//
// Created by Grages, Philip on 04.06.18.
//

#ifndef A_STAR_PATHCALCULATOR_H
#define A_STAR_PATHCALCULATOR_H

#include <map>
#include <list>

#include "JsonReader.h"
#include "Node.h"
#include "Edge.h"
#include "AStar.h"

using namespace std;

class PathCalculator{
private:
    string _edge_path;
    string _node_path;
public:
    PathCalculator(node_path,edge_path);
    vector<Checkpoint> getPath(float x_position, float y_position, int id);

};


#endif //A_STAR_PATHCALCULATOR_H
