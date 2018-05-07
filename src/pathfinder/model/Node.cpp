//
// Created by Grages, Philip on 07.05.18.
//
class Node{
private:
    int _id;
    int x_position;
    int y_position;

public:
    void Node(int _id, int x_position, int y_position){
        this._id = _id;
        this.x_position = x_position;
        this.y_position = y_position;
    }

    int getId(){return _id;}
    array<int,2> getPosition(){return {x_position,y_position};}
};
