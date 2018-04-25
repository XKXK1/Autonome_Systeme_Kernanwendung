#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

#include "topicSubscriber.h"
#include "topicPublisher.h"

#include <thread>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "guidebot");
  ros::NodeHandle node;

  Synchronizer syn;
  TopicSubscriber sub(&syn);
  TopicPublisher pub;
  Heartbeat heartbeat(&syn);

  syn.setup(&heartbeat);

  std::thread synThread(&Synchronizer::run, &syn);
  std::thread subThread(&TopicSubscriber::run, &sub);
  pub.setup();

  subThread.join();
  syn.stop();
  synThread.join();


  /*

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
    return 0;
  }

  move_base_msgs::MoveBaseGoal goal;

  //we'll send a goal to the robot to move 1 meter forward
  //goal.target_pose.header.frame_id = "base_link";
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  

  goal.target_pose.pose.position.x = 38.3113059998;
  goal.target_pose.pose.position.y = -11.7478208542;
  goal.target_pose.pose.orientation.w = 1.0;

  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  ac.waitForResult();

  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved 1 meter forward");
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");

*/

  return 0;
}
