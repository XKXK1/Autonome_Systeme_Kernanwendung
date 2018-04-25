#ifndef TEST_H
#define TEST_H

#include "synchronizer.h"

class Test{
    private:
    Synchronizer *_synchronizer;

    public:
    Test(Synchronizer *synchronizer);

    bool heartbeatTest();

};

#endif