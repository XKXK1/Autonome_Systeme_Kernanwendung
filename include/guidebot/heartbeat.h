#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include "synchronizer.h"

class Synchronizer;

class Heartbeat{
private:
    static constexpr float _sleep_time = 0.25; //* variable used to determine the heartbeat rate

    Synchronizer *_synchronizer; //* pointer to the synchronizer object
    bool _alive; //* used to keep track of heartbeats and if the timer has to be refreshed
    bool _running; //* used for keeping the thread loop alive
    /**
        Timer thread function, if alive is set to true sets it to false and sleeps for _sleep_time
        if alive is still set to false after waking up send an event back to synchronizer
    */
    void _timer();
    std::thread _heartbeat_thread; //* the thread in which _timer is running
    std::mutex _m; //* mutex for all variables
    std::condition_variable _cv; //* used to make the heartbeat sleep if no heartbeat was recieved, and wakes it up to start the timer

public:
    Heartbeat(Synchronizer *synchronizer);
    ~Heartbeat();
    /**
        Wakes up the _timer thread and sets alive to true
    */
    void beat();
    /**
        Cleans the heartbeat class up
    */
    void cleanup();
};

#endif
