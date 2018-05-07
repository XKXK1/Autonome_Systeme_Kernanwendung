#ifndef TOPIC_PUBLISHER_H
#define TOPIC_PUBLISHER_H

#include <vector>
#include <ros/ros.h>

class TopicPublisher{
    private:
    ros::Publisher _heartbeat_out_publisher;

    public:
    TopicPublisher();
    ~TopicPublisher();
    void setup();

    void heartbeat_out();
};

#endif