#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include "topicSubscriber.h"

#include <thread>
#include <string>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "guidebot");
  ros::NodeHandle node;

  //std::string node_path = ros::package::getPath("guidebot");
  //std::string edge_path = node_path;

  //node_path += std::string("/res/nodes.json");
  //edge_path += std::string("/res/edges.json");

  Synchronizer syn;
  TopicSubscriber sub(&syn);
  TopicPublisher pub;
  Heartbeat heartbeat(&syn);
  Driver driver(&syn);
  PathCalculator pathCalculator("/home/campusbot/dev/p3dx_navigation/src/guidebot/res/nodes_foyer.json", "/home/campusbot/dev/p3dx_navigation/src/guidebot/res/edges_foyer.json");

  ROS_INFO("All classes have been initialized start setup");


  pub.setup();
  syn.setup(&heartbeat, &driver, &pathCalculator, &pub);

  ROS_INFO("Setup complete starting program");

  std::thread synThread(&Synchronizer::run, &syn);
  std::thread subThread(&TopicSubscriber::run, &sub);

  subThread.join();
  syn.stop();
  synThread.join();

  ROS_INFO("Programm ended.");

  return 0;
}
