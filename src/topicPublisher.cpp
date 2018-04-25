#include "topicPublisher.h"
#include "std_msgs/String.h"


TopicPublisher::TopicPublisher(){}
TopicPublisher::~TopicPublisher(){}

void TopicPublisher::setup(){

    ros::NodeHandle node;
    ros::Publisher pub = node.advertise<std_msgs::String>("heartbeat_in", 100);
    
    
  ros::Rate loop_rate(10);
  int count = 0;
  while (count < 5)
  {
    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    //ROS_INFO("%s", msg.data.c_str());

    pub.publish(msg);

    ros::spinOnce();
    loop_rate.sleep();
    ++count;
  }


}