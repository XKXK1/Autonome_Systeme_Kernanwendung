#include<synchronizer.h>
#include <ros/ros.h>

#include <iostream>

Synchronizer::Synchronizer() : _buffer(_max_buffer_size), _heartbeat(nullptr), _driver(nullptr), _pathCalculator(nullptr), _publisher(nullptr){}
Synchronizer::~Synchronizer(){}

void Synchronizer::run(){
    while (ros::ok())
    {
        struct Synchronizer_Event event = _buffer.pop();
        if(event. event_type != Synchronizer_Event_Type::STOP){
            switch(event. event_type){
                case Synchronizer_Event_Type::HEARTBEAT_IN: _heartbeat_in_event(); break;
                case Synchronizer_Event_Type::HEARTBEAT_TRIGGER: _heartbeat_out_event(); break;
                case Synchronizer_Event_Type::SELECT_ID: _select_id_event(event.argument);break;
            }
        }
    }
    _heartbeat->cleanup();
    _driver->cleanup();

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

void Synchronizer::setup(Heartbeat *heartbeat, Driver* driver,PathCalculator* pathCalculator, TopicPublisher* publisher){
     _heartbeat = heartbeat;
     _driver = driver;
     _publisher = publisher;
     _pathCalculator = pathCalculator;
}

void Synchronizer::setPosition(float x, float y){
    std::lock_guard<std::mutex> lk(_position_mux);
    _position_x = x;
    _position_y = y;

}
void Synchronizer::getPosition(float &x, float &y){
    std::lock_guard<std::mutex> lk(_position_mux);
    x = _position_x;
    y = _position_y;
}

void Synchronizer::_heartbeat_in_event(){
    _heartbeat->beat();
    _driver->resume();
    _publisher->heartbeat_out();
}

void Synchronizer::_heartbeat_out_event(){
    _driver->pause();
}

void Synchronizer::_select_id_event(int32_t id){
    //_driver->stop();
    float x, y;
    getPosition(x, y);
    ROS_INFO("Starting path calculator");
    std::vector<Checkpoint> checkpoints = _pathCalculator->getPath(x, y, id);
    ROS_INFO("Path calculator finished");

    for(int i = 0; checkpoints.size(); i++){
        std::cout << "POS: x = " << checkpoints[i].x_position << " | y = " << checkpoints[i].y_position << std::endl;
    }
}