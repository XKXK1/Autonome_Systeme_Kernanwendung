#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include "topicSubscriber.h"

#include <thread>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "guidebot");
  ros::NodeHandle node;

  Synchronizer syn;
  TopicSubscriber sub(&syn);
  TopicPublisher pub;
  Heartbeat heartbeat(&syn);
  Driver driver(&syn);

  pub.setup();
  syn.setup(&heartbeat, &driver, &pub);

  std::thread synThread(&Synchronizer::run, &syn);
  std::thread subThread(&TopicSubscriber::run, &sub);

  subThread.join();
  syn.stop();
  synThread.join();

  ROS_INFO("Programm ended.");

  return 0;
}
