#include "heartbeat.h"
#include <ros/ros.h>

Heartbeat::Heartbeat(Synchronizer *synchronizer):_synchronizer(synchronizer),_running(true),_alive(false){
    _heartbeat_thread = std::thread(&Heartbeat::_timer, this);
}

Heartbeat::~Heartbeat(){
    //stop();
}

void Heartbeat::beat(){
    std::lock_guard<std::mutex> lk(_m);
    _alive = true;
    _cv.notify_one();
}

void Heartbeat::_timer(){
    while(_running){

        {
            std::unique_lock<std::mutex> lk(_m);
            while(!_alive && _running){ _cv.wait(lk); }
            _alive = false;
            if(!_running){ return; }
        }

        ros::Duration(_sleep_time).sleep();

        _m.lock();
        if(!_alive){
            struct Synchronizer_Event new_event;
            new_event.event_type = Synchronizer_Event_Type::HEARTBEAT_TRIGGER;
            new_event.argument = 1;
            _synchronizer->addEvent(new_event);
            #if DEBUG
                ROS_INFO("Heartbeat trigger event sent");
            #endif
        }
        _m.unlock();
    }
}

void Heartbeat::cleanup(){
    {
    std::lock_guard<std::mutex> lk(_m);
    _running = false;
    _cv.notify_one();
    }
    _heartbeat_thread.join();
}