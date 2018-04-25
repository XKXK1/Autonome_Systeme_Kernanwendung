#include<synchronizer.h>
#include <ros/ros.h>

Synchronizer::Synchronizer() : _buffer(_max_buffer_size), _heartbeat(nullptr){}
Synchronizer::~Synchronizer(){}

void Synchronizer::run(){
    while (ros::ok())
    {
        struct Synchronizer_Event event = _buffer.pop();
        if(event. event_type != Synchronizer_Event_Type::STOP){
            switch(event. event_type){
                case Synchronizer_Event_Type::HEARTBEAT_IN: _heartbeat_in_event(); break;
                case Synchronizer_Event_Type::HEARTBEAT_OUT: _heartbeat_out_event(); break;
            }
            ROS_INFO("Event recv: %i", event.argument);
        }
    }

    _heartbeat->stop();

    ROS_INFO("Synchronizer ended");
}
void Synchronizer::addEvent(struct Synchronizer_Event new_event){
    _buffer.push(new_event);
}

void Synchronizer::stop(){
    struct Synchronizer_Event new_event;
    new_event.event_type = Synchronizer_Event_Type::STOP;
    _buffer.push(new_event);
}

void Synchronizer::setup(Heartbeat *heartbeat){
     _heartbeat = heartbeat;
}

void Synchronizer::_heartbeat_in_event(){
    _heartbeat->beat();

}
void Synchronizer::_heartbeat_out_event(){

}