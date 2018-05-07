#ifndef DRIVER_H
#define DRIVER_H

#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

#include "checkpoint.h"
#include "synchronizer.h"

class Synchronizer;
//typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class Driver {
private:
    std::vector<Checkpoint> _checkpoints; //* Vector of all checkpoints the driver has to move trough
    actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> _ac; //* object used for sending goals to ros
    std::thread _driver_thread; //* thread handler for the driver
    std::mutex _m; //* mutex for all variables
    std::condition_variable _cv; //* used to make the heartbeat sleep if no heartbeat was recieved, and wakes it up to start the timer
    Synchronizer* _synchronizer;

    int _current_index; //* Variable keeping track of the current checkpoint we are moving towards to
    bool _in_action; //* Variable keeping track if the driver is able to operate
    bool _running; //* Variable used for keeping the driver thread alive and closing it when needed

    /**
    The main driver thread. Its used for sending the goals to ros and stopping it
    */
    void _run();
    /**
    Checks if the reached cheackpoint is the last one, if yes notify the synchronizer, else move towards the next one
    */
    void _checkpointReached();
    /**
    Checks if the movement failed because of the driver itself or another reason and lets the synchronizer know
    */
    void _checkpointFailed();


public:
    Driver(Synchronizer* synchronizer);
    ~Driver();

    /**
    Sets the driver checkpoint list and lets it know that its able to drive
    @param checkpoints a list of checkpoints the driver should move trough
    */
    void start(std::vector<Checkpoint> checkpoints);
    /**
    Stops the driver, clears its checkpoint vector and sets it in non drivable state
    */
    void stop();
    /**
    Pauses the driver and sends an cancel current goal message
    */
    void pause();
    /**
    Resumes the driver for further driving if its in drive state
    */
    void resume();
    /**
    Cleans up the driver by deleting all checkpoints and stopping the driver thread
    */
    void cleanup(); // prepare closing 

    
};


#endif
