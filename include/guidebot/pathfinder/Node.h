#pragma once
class Node {
private:
	float _x_position;
	float _y_position;
	int _id;
public:
	Node(int id, float x_position, float y_position);
	Node();

	bool operator == (const Node& n) const;
	bool operator != (const Node& n) const;
	int getId() const;
	float getXPosition();
	float getYPosition();
	float z_rotation;
	float w_rotation;
};

