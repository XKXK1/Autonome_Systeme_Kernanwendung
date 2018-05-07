#include "driver.h"

#include <move_base_msgs/MoveBaseAction.h>

Driver::Driver(Synchronizer* synchronizer) : _ac("move_base", true), _synchronizer(synchronizer), _running(true), _in_action(false), _current_index(0){
    _driver_thread = std::thread(&Driver::_run, this);
}

Driver::~Driver(){}

void Driver::_run(){
    while(_running){
        {
        std::unique_lock<std::mutex> lk(_m);
        while(!_in_action && _running){ _cv.wait(lk); }
        if(!_running){ return; }
        }

        if(_current_index < _checkpoints.size()){  
            move_base_msgs::MoveBaseGoal goal;  
            goal.target_pose.header.frame_id = "map";
            goal.target_pose.header.stamp = ros::Time::now();
            //goal.target_pose.pose.position.x = 38.3113059998;
            //goal.target_pose.pose.position.y = -11.7478208542;
            goal.target_pose.pose.position.x = _checkpoints[_current_index].x_position;
            goal.target_pose.pose.position.y = _checkpoints[_current_index].y_position;
            goal.target_pose.pose.orientation.w = 1.0;

            #if DEBUG
                ROS_INFO("Sending goal");
            #endif
            _ac.sendGoal(goal);
            _ac.waitForResult();

            if(_ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
                #if DEBUG
                    ROS_INFO("Checkpoint reached");
                #endif
                _checkpointReached();
            }
            else{
                #if DEBUG
                    ROS_INFO("Failed to reach checkpoint");
                #endif
            }
        }
    }
}

void Driver::_checkpointReached(){
    _current_index++;
    if(_current_index == _checkpoints.size()){
        _in_action = false;
    }
}

void Driver::_checkpointFailed(){}

void Driver::start(std::vector<Checkpoint> checkpoints){
    std::lock_guard<std::mutex> lk(_m);
    if(!_in_action){
        _checkpoints = checkpoints;
        _current_index = 0;
    }
    #if DEBUG
        ROS_INFO("Driver started");
    #endif
}

void Driver::stop(){
    std::lock_guard<std::mutex> lk(_m);
    if(!_in_action){
        _checkpoints.clear();
        _current_index = 0;
        _ac.cancelGoal();
    }
    #if DEBUG
        ROS_INFO("Driver stoped");
    #endif
}


void Driver::pause(){
    std::lock_guard<std::mutex> lk(_m);
    if(_in_action){
        _in_action = false;
        _ac.cancelGoal();
    }
    #if DEBUG
        ROS_INFO("Driver paused");
    #endif
}

void Driver::resume(){
    std::lock_guard<std::mutex> lk(_m);
    if(!_in_action){
        _in_action = true;
        _cv.notify_one();
    }
    #if DEBUG
        ROS_INFO("Driver resumed");
    #endif
}

void Driver::cleanup(){
    {
    std::lock_guard<std::mutex> lk(_m);
    if(_in_action){
        _in_action = false;
        _ac.cancelGoal();
    }
    _running = false;
    _cv.notify_one();
    }

    _driver_thread.join();
}

