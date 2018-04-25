#include "heartbeat.h"
#include <ros/ros.h>

Heartbeat::Heartbeat(Synchronizer *synchronizer):_synchronizer(synchronizer),_running(false),_alive(false){
}

Heartbeat::~Heartbeat(){
}

void Heartbeat::beat(){
    _m.lock();
    if(!_running){   
         _running = true;
        _heartbeatThread = std::thread(&Heartbeat::_timer, this);
    } else {
        _alive = true;
    }
    _m.unlock();
}

void Heartbeat::_timer(){
    while(_running){
        _m.lock();
        _alive = false;
        _m.unlock();

        ros::Duration(_sleep_time).sleep();

         _m.lock();
        if(!_alive){
            _running = false;
        }
        _m.unlock();
    }

    struct Synchronizer_Event new_event;
    new_event.event_type = Synchronizer_Event_Type::HEARTBEAT_OUT;
    new_event.argument = 1;
    _synchronizer->addEvent(new_event);
}

void Heartbeat::stop(){
    _m.lock();
    _running = false;
    _m.unlock();
    _heartbeatThread.join();
}