#include "topicSubscriber.h"
#include <ros/ros.h>
#include <tf/transform_listener.h>

TopicSubscriber::TopicSubscriber(Synchronizer *synchronizer) : _synchronizer(synchronizer){}
TopicSubscriber::~TopicSubscriber(){}

static void _listen(){
    ros::spin();
}

void TopicSubscriber::run(){
    ros::NodeHandle node;
    ros::Subscriber heartbeat_in_sub = node.subscribe("heartbeat_in", 100, &TopicSubscriber::_heartbeat_in, this);
    ros::Subscriber id_in_sub = node.subscribe("navigationTarget", 100, &TopicSubscriber::_id_in, this);

    std::thread spin_thread(_listen);

    tf::TransformListener listener;

    ros::Rate rate(10.0);
    while(node.ok()){
        tf::StampedTransform transform;
        try{
            listener.lookupTransform("/map", "base_link", ros::Time(0), transform);
            _synchronizer->setPosition(transform.getOrigin().x(), transform.getOrigin().y());
        }catch(tf::TransformException &ex){
            ROS_ERROR("%s", ex.what());
            ros::Duration(1.0).sleep();
            continue;
        }

        rate.sleep();
    }
    
    spin_thread.join();
    ROS_INFO("Topic subscriber ended");
}

void TopicSubscriber::_heartbeat_in(const std_msgs::Int32::ConstPtr& msg){
    struct Synchronizer_Event event;
    event.event_type = Synchronizer_Event_Type::HEARTBEAT_IN;
    event.argument = 0;
    _synchronizer->addEvent(event);
}

void TopicSubscriber::_id_in(const std_msgs::Int32::ConstPtr& msg){
    struct Synchronizer_Event event;
    event.event_type = Synchronizer_Event_Type::SELECT_ID;
    event.argument = msg->data;
    _synchronizer->addEvent(event);
}