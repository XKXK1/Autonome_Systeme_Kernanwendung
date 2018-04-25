#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include <thread>
#include <mutex>
#include "synchronizer.h"

class Synchronizer;

class Heartbeat{
private:
    Synchronizer *_synchronizer;
    bool _alive;
    bool _running;
    static constexpr float _sleep_time = 5.0;//0.25;
    void _timer();
    std::thread _heartbeatThread;
    std::mutex _m;

public:
    Heartbeat(Synchronizer *synchronizer);
    ~Heartbeat();
    void beat();
    void stop();
};

#endif
