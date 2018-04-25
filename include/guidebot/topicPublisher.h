#ifndef TOPIC_PUBLISHER_H
#define TOPICPUBLISHER_H

#include <vector>
#include <ros/ros.h>

class TopicPublisher{
    private:
    std::vector<ros::Publisher> _publisher;

    public:
    TopicPublisher();
    ~TopicPublisher();
    void setup();

};

#endif