#include "topicSubscriber.h"
#include <ros/ros.h>

TopicSubscriber::TopicSubscriber(Synchronizer *synchronizer) : _synchronizer(synchronizer){}
TopicSubscriber::~TopicSubscriber(){}

void TopicSubscriber::run(){
    ros::NodeHandle node;
    ros::Subscriber heartbeat_in_sub = node.subscribe("heartbeat_in", 100, &TopicSubscriber::_heartbeat_in, this);
    
    ros::spin();
    ROS_INFO("Topic subscriber ended");
}

static int love = 0;

void TopicSubscriber::_heartbeat_in(const std_msgs::String::ConstPtr& msg){
    //ROS_INFO("I heard: [%s]", msg->data.c_str());
    struct Synchronizer_Event event;
    event.event_type = Synchronizer_Event_Type::HEARTBEAT_IN;
    event.argument = 0;
    _synchronizer->addEvent(event);
}






