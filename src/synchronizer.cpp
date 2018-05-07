#include<synchronizer.h>
#include <ros/ros.h>

Synchronizer::Synchronizer() : _buffer(_max_buffer_size), _heartbeat(nullptr){}
Synchronizer::~Synchronizer(){}

void Synchronizer::run(){
    std::vector<Checkpoint> test;
    Checkpoint testPoint(38.3113059998, -11.7478208542);
    test.push_back(testPoint);
    _driver->start(test);
    while (ros::ok())
    {
        struct Synchronizer_Event event = _buffer.pop();
        if(event. event_type != Synchronizer_Event_Type::STOP){
            switch(event. event_type){
                case Synchronizer_Event_Type::HEARTBEAT_IN: _heartbeat_in_event(); break;
                case Synchronizer_Event_Type::HEARTBEAT_TRIGGER: _heartbeat_out_event(); break;
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

void Synchronizer::setup(Heartbeat *heartbeat, Driver* driver, TopicPublisher* publisher){
     _heartbeat = heartbeat;
     _driver = driver;
     _publisher = publisher;
}

void Synchronizer::_heartbeat_in_event(){
    _heartbeat->beat();
    _driver->resume();
    _publisher->heartbeat_out();

}
void Synchronizer::_heartbeat_out_event(){
    _driver->pause();
}