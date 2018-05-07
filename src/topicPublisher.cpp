#include "topicPublisher.h"
#include "std_msgs/Int32.h"


TopicPublisher::TopicPublisher(){}
TopicPublisher::~TopicPublisher(){}

void TopicPublisher::setup(){

  ros::NodeHandle node;
  _heartbeat_out_publisher = node.advertise<std_msgs::Int32>("heartbeat_out", 100);

  //ros::spinOnce();

}

void TopicPublisher::heartbeat_out(){
      std_msgs::Int32 msg;
      msg.data = 1;
      _heartbeat_out_publisher.publish(msg);
}