#pragma once
class Node {
	int _x_position;
	int _y_position;
	int _id;
public:
	Node(int id, int x_position, int y_position);
	Node();

	bool operator == (const Node& n) const;
	bool operator != (const Node& n) const;
	int getId() const;
	int getXPosition();
	int getYPosition();
};

