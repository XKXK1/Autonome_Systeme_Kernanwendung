#include "Node.h"


Node::Node(int id, float x_position, float y_position)
{
	_id = id;
	_x_position = x_position;
	_y_position = y_position;
}
Node::Node(){}

int Node::getId() const {
	return _id;
}
bool Node::operator==(const Node &n) const {
    return _id == n._id;
}
bool Node::operator!=(const Node &n) const {
    return _id != n._id;
}
float Node::getXPosition() { return _x_position; }
float Node::getYPosition() { return _y_position; }

