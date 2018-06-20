#ifndef CHECKPOINT_H
#define CHECKPOINT_H

class Checkpoint{
    private:

    public:
    Checkpoint();
    ~Checkpoint();
    Checkpoint(float x, float y, float z, float w);

    float x_position;
    float y_position;
    float z_rotation;
    float w_rotation;

};

#endif